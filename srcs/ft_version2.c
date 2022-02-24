/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_version2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:48:08 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/24 19:08:05 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_elem_is_redirection(t_elem *elem)
{
	return (elem->type == IN || elem->type == DOUBLE_IN || elem->type == OUT || elem->type == DOUBLE_OUT);
}

static int	ft_elem_get_cmd_args_count(t_elem *cursor)
{
	int		i;

	i = 0;
	while (cursor)
	{
		if (cursor->type == PIPE)
			break ;
		if (ft_elem_is_redirection(cursor))
		{
			cursor = cursor->next->next;
			continue ;
		}
		cursor = cursor->next;
		i++;
	}
	return (i);
}

static char	**ft_elem_get_cmd_args(t_data **data, t_elem *cursor)
{
	char	**cmd_tab;
	int		i;

	(void) data;
	i = 0;
	cmd_tab = malloc(sizeof(char*) * (ft_elem_get_cmd_args_count(cursor) + 1));
	if (!cmd_tab)
		return (0);
	while (cursor)
	{
		if (cursor->type == PIPE)
			break ;
		if (ft_elem_is_redirection(cursor))
		{
			cursor = cursor->next->next;
			continue ;
		}
		cmd_tab[i] = cursor->str;
		cursor = cursor->next;
		i++;
	}
	cmd_tab[i] = 0;
	return (cmd_tab);
}

static t_elem	*ft_elem_get_right(t_elem *cursor)
{
	while (cursor)
	{
		if (cursor->type == PIPE)
			return (cursor->next);
		cursor = cursor->next;
	}
	return (0);
}

static t_elem	*ft_elem_clone_left(t_elem *cursor)
{
	t_elem		*res;

	res = malloc(sizeof(t_elem));
	if (!res)
		return (0);
	res->type = cursor->type;
	res->str = ft_strdup(cursor->str);
	if (cursor->next && cursor->next->type != PIPE)
		res->next = ft_elem_clone_left(cursor->next);
	else
		res->next = 0;
	return (res);
}

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
	int std[2];
    int fd[2];
	int	pid;
	
	if (pipe(fd) == -1)
		return ;
	std[0] = dup(STDIN_FILENO);
	std[1] = dup(STDOUT_FILENO);
    pid = fork();
	if (pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return ;
	}
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
    } else
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

// wc < info.txt > out.txt | cat -e

void    ft_execute_command(t_data **data, t_elem *list, char **envp)
{
	int	pid;

	pid = 0;
    if (!ft_there_is_pipe(list))
   	{
   		// if (is_build_in)
   			// run_bi
   		// else
		pid = fork();
		if (pid == 0)
		{
			char **args = ft_elem_get_cmd_args(data, list);
			if (!args)
				return ;
			// ft_replace_in_by_redtirection_in();
			ft_run_execve_with_all_path(ft_getenv(data, "PATH")->value, args);
			// ft_replace_out_by_redtirection_out();
		}
		else
			waitpid(pid, 0, 0); // Add flags
	} else
		ft_execute_pipe(data, list, envp);
}
