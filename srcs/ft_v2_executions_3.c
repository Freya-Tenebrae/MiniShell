/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_executions_3.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 12:38:12 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 12:46:53 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_there_is_pipe(t_elem *cursor)
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

int	ft_execute_pipe(t_data **data, t_elem *list)
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
