/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:18:49 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/27 15:56:48 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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

void	ft_run_line(char **str, t_data **data)
{
	int		ret;
	int		res_parse_line;
	t_elem	*list;

	res_parse_line = ft_parse_line(data, str, &ret, &list);
	if (res_parse_line == 0 && ft_pipe_is_present_on_line(list) == 0)
		g_status_minishell = 2;
	else
		g_status_minishell = 1;
	if (res_parse_line == 0)
	{
		if (ft_check_syntaxe_operator(list) == 0)
		{
			ft_open_redirections(list);
			ft_execute_command(data, list, (*data)->envp);
		}
		ft_free_elem(&list);
	}
}
