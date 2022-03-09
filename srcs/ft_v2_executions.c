/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_executions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:48:08 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/09 10:28:31 by gadeneux         ###   ########.fr       */
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
	int		std[2];
	int		fd[2];
	int		pid;
	t_elem	*list_left;

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
		list_left = ft_elem_clone_left(list);
		ft_execute_command(data, list_left, envp);
		ft_free_elem(&list_left);
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
	int		result_execve;
	char	**cmd_args;
	int		fd[2];
	int		pid;

	pid = 0;
	if (!ft_there_is_pipe(list))
	{
		cmd_args = ft_elem_get_cmd_args(data, list);
		
		if (ft_is_build_in(cmd_args[0]) == 1)
		{
			ft_run_bi(data, cmd_args);
			free(cmd_args);
			return (0);
		}
		free(cmd_args);
		pid = fork();
		if (pid == 0)
		{
			if (ft_redirection_in_present(list))
			{				
				if (!ft_redirection_get_in(list) || \
					ft_redirection_get_in(list) == NULL)
				{
					// Gestion d'erreur, get filename 
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
			cmd_args = ft_elem_get_cmd_args(data, list);
			result_execve = ft_run_execve_with_all_path(\
				ft_getenv(data, "PATH")->value, cmd_args);
			if (result_execve == -1)
				ft_put_error(GENERIC_ERROR, "malloc error");
			else
				ft_put_error(CMD_NOT_FOUND_ERROR, cmd_args[0]);
			free(cmd_args);
			exit(0);
		}
		else
		{
			int status = 0;
			waitpid(pid, &status, 0); // Add flags
			g_status_minishell.status_pipe = WEXITSTATUS(status);
		}
	}
	else
	{
		ft_execute_pipe(data, list, envp);
	}
	return (0);
}
