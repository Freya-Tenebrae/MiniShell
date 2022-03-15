/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_executions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:48:08 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/15 13:27:57 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_there_is_pipe(t_elem *cursor)
{
	while (cursor)
	{
		if (cursor->type == PIPE)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

static int	ft_execute_pipe_child(t_data **data, t_elem *list, int *std,
	int *fd)
{
	t_elem	*list_left;

	close(std[0]);
	close(std[1]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	list_left = ft_elem_clone_left(list);
	ft_execute_command(data, list_left);
	ft_free_elem(&list_left);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(0);
}

static void	ft_execute_pipe_parent(t_data **data, t_elem *list, int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);
	ft_execute_command(data, ft_elem_get_right(list));
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	wait(NULL);
}

static int	ft_execute_pipe(t_data **data, t_elem *list)
{
	int		std[2];
	int		fd[2];
	int		pid;

	if (pipe(fd) == -1)
		return (-1);
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
	{
		close(std[0]);
		close(std[1]);
		return (-1);
	}
	if (pid == 0)
		ft_execute_pipe_child(data, list, std, fd);
	else
		ft_execute_pipe_parent(data, list, fd);
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
	return (0);
}

static void	redirections2(t_elem *list)
{
	if (ft_redirection_out_present(list))
	{
		dup2(list->out_fd, STDOUT_FILENO);
		close(list->out_fd);
		list->out_fd = -1;
	}
}

int	redirections(t_elem *list)
{
	char	*content_redirection_in;
	char	*filename_in;
	int		fd[2];

	if (ft_check_access_ok(list) != 0)
		return (-1);
	if (ft_redirection_in_present(list))
	{
		content_redirection_in = ft_redirection_get_in(list);
		if (!content_redirection_in || content_redirection_in == NULL)
		{
			filename_in = ft_get_filename_in(list);
			ft_put_error(FILE_ERROR, filename_in);
			return (-1);
		}	
		if (pipe(fd) == -1)
			return (-1);
		ft_putstr_fd(content_redirection_in, fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
	}
	redirections2(list);
	return (0);
}

static int	ft_execute_command_bi(t_data **data, t_elem *list)
{
	int		redirection_ret;
	int		standard[2];
	char	**cmd_args;

	cmd_args = ft_elem_get_cmd_args(data, list);
	if (ft_is_build_in(cmd_args[0]) == 1)
	{
		standard[0] = dup(STDIN_FILENO);
		standard[1] = dup(STDOUT_FILENO);
		redirection_ret = redirections(list);
		if (redirection_ret == 0)
			g_status_minishell.status_pipe = ft_run_bi(data, cmd_args);
		dup2(standard[0], STDIN_FILENO);
		dup2(standard[1], STDOUT_FILENO);
		close(standard[0]);
		close(standard[1]);
		free(cmd_args);
		return (1);
	}
	else
		free(cmd_args);
	return (0);
}

static void	ft_execute_command_child_manage_errors(int result_execve,
	char **cmd_args, int *pipe_exit_code)
{
	if (result_execve == -1)
	{
		*pipe_exit_code = 2;
		ft_put_error(GENERIC_ERROR, "malloc error");
	}
	else if (result_execve == -2)
	{
		*pipe_exit_code = 127;
		ft_put_error(FILE_ERROR, cmd_args[0]);
	}
	else if (result_execve == -3)
	{
		*pipe_exit_code = 126;
		ft_put_error(ACCESS_ERROR, cmd_args[0]);
	}
	else if (result_execve == -4)
	{
		*pipe_exit_code = 126;
		ft_put_error(IS_DIRECTORY_ERROR, cmd_args[0]);
	}
	else
	{
		*pipe_exit_code = 127;
		ft_put_error(CMD_NOT_FOUND_ERROR, cmd_args[0]);
	}
}

static void	ft_execute_command_child(t_data **data, t_elem *list,
	int *pipe_exit_code)
{
	int		result_execve;
	char	**cmd_args;

	*pipe_exit_code = 0;
	cmd_args = ft_elem_get_cmd_args(data, list);
	result_execve = ft_run_execve_with_all_path(
			ft_getenv(data, "PATH")->value, cmd_args, data);
	// if (result_execve != -1)
	// 	free(cmd_args);
	ft_execute_command_child_manage_errors(result_execve, cmd_args,
		pipe_exit_code);
}

static void	ft_execute_command_parent(int *pipe_exit_code_fd, int pid)
{
	int		pipe_exit_code;
	int		status;

	pipe_exit_code = 0;
	close(pipe_exit_code_fd[1]);
	read(pipe_exit_code_fd[0], &pipe_exit_code, sizeof(int));
	close(pipe_exit_code_fd[0]);
	status = 0;
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	else if (pipe_exit_code != 0)
		g_status_minishell.status_pipe = pipe_exit_code;
	else if (WIFEXITED(status))
		g_status_minishell.status_pipe = WEXITSTATUS(status);
}

static void	ft_execute_command_redirect(t_data **data, t_elem *list,
	int *pipe_exit_code_fd, int *pipe_exit_code)
{
	int		redirection_ret;

	redirection_ret = redirections(list);
	if (redirection_ret == 0)
	{
		ft_execute_command_child(data, list, pipe_exit_code);
		close(pipe_exit_code_fd[0]);
		write(pipe_exit_code_fd[1], pipe_exit_code, sizeof(int));
		close(pipe_exit_code_fd[1]);
	}
	else
	{
		*pipe_exit_code = 1;
		close(pipe_exit_code_fd[0]);
		write(pipe_exit_code_fd[1], pipe_exit_code, sizeof(int));
		close(pipe_exit_code_fd[1]);
	}
}

void	ft_execute_command2(t_data **data, t_elem *list, int *pipe_exit_code_fd,
		int *pipe_exit_code)
{
	ft_execute_command_redirect(data, list, pipe_exit_code_fd,
		pipe_exit_code);
	exit(0);
}

void	ft_execute_command(t_data **data, t_elem *list)
{
	int		pipe_exit_code_fd[2];
	int		pipe_exit_code;
	int		pid;

	pid = 0;
	if (!ft_there_is_pipe(list))
	{
		if (ft_execute_command_bi(data, list))
			return ;
		if (pipe(pipe_exit_code_fd) == -1)
			return ;
		pid = fork();
		if (pid == -1)
			return ;
		if (pid == 0)
			ft_execute_command2(data, list, pipe_exit_code_fd, &pipe_exit_code);
		else
			ft_execute_command_parent(pipe_exit_code_fd, pid);
	}
	else
		ft_execute_pipe(data, list);
}
