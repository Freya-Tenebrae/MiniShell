/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_executions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:48:08 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 12:42:42 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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
