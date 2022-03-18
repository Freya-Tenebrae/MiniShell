/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_executions_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:25:39 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/18 17:15:48 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_execute_command_child_manage_errors_2(int result_execve,
	char ***cmd_args, int *pipe_exit_code)
{
	if (result_execve == -5)
	{
		*pipe_exit_code = 2;
		ft_put_error(GENERIC_ERROR, "error: PATH not set");
	}
	else
	{
		*pipe_exit_code = 127;
		ft_put_error(CMD_NOT_FOUND_ERROR, (*cmd_args)[0]);
	}
}

static void	ft_execute_command_child_manage_errors(int result_execve,
	char ***cmd_args, int *pipe_exit_code)
{
	if (result_execve == -2)
	{
		*pipe_exit_code = 127;
		ft_put_error(FILE_ERROR, (*cmd_args)[0]);
	}
	else if (result_execve == -3)
	{
		*pipe_exit_code = 126;
		ft_put_error(ACCESS_ERROR, (*cmd_args)[0]);
	}
	else if (result_execve == -4)
	{
		*pipe_exit_code = 126;
		ft_put_error(IS_DIRECTORY_ERROR, (*cmd_args)[0]);
	}
	else
	{
		ft_execute_command_child_manage_errors_2(result_execve, cmd_args, \
																pipe_exit_code);
	}
	free(*cmd_args);
}

void	ft_execute_command_child(t_data **data, t_elem *list,
	int *pipe_exit_code)
{
	int		result_execve;
	char	**cmd_args;
	t_env	*path_env;
	char	*path;

	*pipe_exit_code = 0;
	cmd_args = ft_elem_get_cmd_args(data, list);
	path_env = ft_getenv(data, "PATH");
	if (!path_env || path_env == NULL)
		result_execve = -5;
	else
	{
		path = path_env->value;
		result_execve = ft_run_execve_with_all_path(path, cmd_args, data);
	}
	if (result_execve == -1)
	{
		free(cmd_args);
		*pipe_exit_code = 2;
		ft_put_error(GENERIC_ERROR, "malloc error");
	}
	else
		ft_execute_command_child_manage_errors(result_execve, &cmd_args,
			pipe_exit_code);
}

void	ft_execute_command_parent(int *pipe_exit_code_fd, int pid)
{
	int		pipe_exit_code;
	int		status;

	pipe_exit_code = 0;
	close(pipe_exit_code_fd[1]);
	read(pipe_exit_code_fd[0], &pipe_exit_code, sizeof(int));
	close(pipe_exit_code_fd[0]);
	status = 0;
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
	// revoir le truc en bas, ne marche pas correctement ... et voir si autoriser ?
	if (WIFSIGNALED(status))
		exit(128 + WTERMSIG(status));
	else if (pipe_exit_code != 0)
		g_status_minishell.status_pipe = pipe_exit_code;
	else if (WIFEXITED(status))
		g_status_minishell.status_pipe = WEXITSTATUS(status);
}
