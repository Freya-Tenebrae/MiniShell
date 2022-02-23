/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_version2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:48:08 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/23 21:48:37 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

// static t_redir	*ft_v2_create_redir(t_elem *elem)
// {
// 	t_redir	*res;

// 	res = malloc(sizeof(t_redir));
// 	if (!res)
// 		return (0);
// 	res->file = ft_strdup(elem->next->str);
// 	res->type = elem->type;
// 	if (!res->file)
// 	{
// 		free(res);
// 		return (0);
// 	}
// 	return (res);
// }

// static t_redir	*ft_v2_read_next_command_in(t_elem *list)
// {
// 	t_elem	*last;

// 	last = 0;
// 	while (list)
// 	{
// 		if (list->type == PIPE)
// 			break ;
// 		if (list->type == IN || list->type == DOUBLE_IN)
// 		{
// 			last = list;
// 			list = list->next->next;
// 			continue ;
// 		}
// 		list = list->next;
// 	}
// 	if (last)
// 		return (ft_v2_create_redir(last));
// 	return (0);
// }

// static t_redir	*ft_v2_read_next_command_out(t_elem *list)
// {
// 	t_elem	*last;

// 	last = 0;
// 	while (list)
// 	{
// 		if (list->type == PIPE)
// 			break ;
// 		if (list->type == OUT || list->type == DOUBLE_OUT)
// 		{
// 			last = list;
// 			list = list->next->next;
// 			continue ;
// 		}
// 		list = list->next;
// 	}
// 	if (last)
// 		return (ft_v2_create_redir(last));
// 	return (0);
// }

static int	ft_pipe_is_present_on_line(t_elem *list)
{
	while (list && list != NULL)
	{
		if (list->type == PIPE)
			return (0);
		list = list->next;
	}
	return (1);
}

static int	ft_parse_line(t_data **data, char **str, int *ret, t_elem **list)
{
	if (!ft_check_quote(*str))
		return (ft_put_error(GENERIC_ERROR, "Quote error"));
	ft_replace_env(data, str);
	*ret = 0;
	*list = ft_read_line(*str, ret);
	if (*list == NULL || *ret != READ_OK)
		return (ft_put_error(GENERIC_ERROR, "Reading line error"));
	return (0);
}

static int	ft_v2_is_redirection(t_elem *elem)
{
	return (elem->type == IN || elem->type == DOUBLE_IN || elem->type == OUT || elem->type == DOUBLE_OUT);
}

static int	ft_v2_read_next_command_tab_length(t_elem *list)
{
	int		i;

	i = 0;
	while (list)
	{
		if (list->type == PIPE)
			break ;
		if (ft_v2_is_redirection(list))
		{
			list = list->next->next;
			continue ;
		}
		list = list->next;
		i++;
	}
	return (i);
}

static char	**ft_v2_read_next_command_args(t_data **data, t_elem *list)
{
	char	**cmd_tab;
	int		i;

	(void) data;
	i = 0;
	cmd_tab = malloc(sizeof(char*) * (ft_v2_read_next_command_tab_length(list) + 1));
	if (!cmd_tab)
		return (0);
	while (list)
	{
		if (list->type == PIPE)
			break ;
		if (ft_v2_is_redirection(list))
		{
			list = list->next->next;
			continue ;
		}
		cmd_tab[i] = list->str;
		list = list->next;
		i++;
	}
	cmd_tab[i] = 0;
	return (cmd_tab);
}

static t_elem	*ft_v2_get_next_command(t_elem *list)
{
	while (list)
	{
		if (list->type == PIPE)
			return (list->next);
		list = list->next;
	}
	return (0);
}

// wc < info.txt > out.txt | cat -e

void    exec(t_data **data, t_elem *list, char **envp);

void    exec_pipe(t_data **data, t_elem *list, char **envp)
{
    int fd[2];

    pipe(fd);

    int pid = fork();
    if (pid == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        exec(data, list, envp);
    }
    else
    {
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
        close(fd[0]);
        exec(data, ft_v2_get_next_command(list), envp);
        wait(NULL);
    }
}

int		there_is_pipe(t_elem *list)
{
	while (list)
	{
		if (list->type == PIPE)
			return (1);
		list = list->next;
	}
	return (0);
}

void    exec(t_data **data, t_elem *list, char **envp)
{
    if (there_is_pipe(list))
    {
		exec_pipe(data, list, envp);
	} else
	{
		char **cmd1_args = ft_v2_read_next_command_args(data, list);
		ft_run_execve_with_all_path(ft_getenv(data, "PATH")->value, cmd1_args);
	}
}

static void	ft_v2_run_command(t_data **data, t_elem *list)
{
	exec(data, list, (*data)->envp);
}

// ls | wc < info.txt > out.txt | cat -e

void	ft_v2_runline(char **cmd, t_data **data)
{
	int		res_parse_line;
	int		ret;
	t_elem	*list;

	res_parse_line = ft_parse_line(data, cmd, &ret, &list);
	if (res_parse_line == 0 && ft_pipe_is_present_on_line(list) == 0)
		g_status_minishell = 2;
	else
		g_status_minishell = 1;
	if (res_parse_line == 0)
	{
		if (ft_check_syntaxe_operator(list) == 0)
			ft_v2_run_command(data, list);
		ft_free_elem(&list);
	}
}