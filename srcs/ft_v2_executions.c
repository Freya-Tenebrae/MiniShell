/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_executions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:48:08 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/03 17:58:06 by cmaginot         ###   ########.fr       */
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

static void	ft_execute_pipe(t_data **data, t_elem *list, char **envp)
{
	int	std[2];
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
		return ;
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
	{
		close(std[0]);
		close(std[1]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		ft_execute_command(data, ft_elem_clone_left(list), envp);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		exit(0);
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		ft_execute_command(data, ft_elem_get_right(list), envp);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		wait(NULL);
	}
	dup2(std[0], STDIN_FILENO);
	dup2(std[1], STDOUT_FILENO);
	close(std[0]);
	close(std[1]);
}

int	ft_execute_command(t_data **data, t_elem *list, char **envp)
{
	int	result_execve;
	int	pid;
	int	fd[2];

	pid = 0;
	if (!ft_there_is_pipe(list))
	{
		pid = fork();
		if (pid == 0)
		{
			if (ft_redirection_in_present(list))
			{				
				if (!ft_redirection_get_in(list) || \
					ft_redirection_get_in(list) == NULL)
				{
					// Gestion d'erreur 
					ft_put_error(FILE_ERROR, "Unknown file");
					exit(0);
				}	
				if (pipe(fd) == -1)
					exit(0);
				ft_putstr_fd(ft_redirection_get_in(list), fd[1]);
				dup2(fd[0], STDIN_FILENO);
				close(fd[0]);
				close(fd[1]);
			}
			if (ft_redirection_out_present(list))
			{
				dup2(list->out_fd, STDOUT_FILENO);
				close(list->out_fd);
				list->out_fd = -1;
			}
			// gerer autrement le truc en bas (leaks et erreur)
			if (ft_is_build_in(ft_elem_get_cmd_args(data, list)[0]) == 1)
			{
				ft_run_bi(data, ft_elem_get_cmd_args(data, list));
				exit(0);
			}
			else
			{
				result_execve = ft_run_execve_with_all_path(\
					ft_getenv(data, "PATH")->value, \
					ft_elem_get_cmd_args(data, list));
				if (result_execve == -1)
					ft_put_error(GENERIC_ERROR, "malloc error");
				else
					ft_put_error(CMD_NOT_FOUND_ERROR, \
						ft_elem_get_cmd_args(data, list)[0]);
				exit(0);
			}
		}
		else
		{
			waitpid(pid, 0, 0); // Add flags
		}
	}
	else
	{
		ft_execute_pipe(data, list, envp);
	}
	return (0);
}
