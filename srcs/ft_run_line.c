/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:18:49 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/22 17:58:22 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static t_elem	*ft_run_cmd_next_line(t_elem *list, char **infile)
{
	if (list->type == ARGUMENT)
		return (ft_run_cmd(list, infile));
	else if (list->type == PIPE)
		return (ft_run_pipe(list, infile));
	else if (list->type == OUT)
		return (ft_tools_push_out(list, infile));
	else if (list->type == DOUBLE_OUT)
		return (ft_tools_push_double_out(list, infile));
	return (NULL);
}

static int	ft_exec_line(int *ret, t_elem **list)
{
	t_elem	*listptr;
	char	*infile;

	if (*ret != READ_OK)
	{
		printf("Error.\n");
		return (1);
	}
	infile = NULL;
	listptr = *list;
	while (listptr && listptr != NULL)
		listptr = ft_run_cmd_next_line(listptr, &infile);
	if (infile && infile != NULL)
		free(infile);
	return (0);
}

static int	ft_pars_line(char **str, int *ret, t_elem **list)
{
	if (!ft_check_quote(*str))
	{
		printf("Quote error.\n");
		return (1);
	}
	ft_replace_env(str);
	*ret = 0;
	*list = ft_read_command(*str, ret);
	return (0);
}

int	ft_run_line(char **str)
{
	int		ret;
	int		res_exec_line;
	t_elem	*list;

	if (ft_strcmp("exit", *str) == 0)
		return (1);
	if (ft_pars_line(str, &ret, &list) != 0)
		return (1);
	res_exec_line = ft_exec_line(&ret, &list);
	ft_tools_free_elem(&list);
	return (res_exec_line);
}
