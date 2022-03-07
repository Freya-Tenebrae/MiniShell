/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:18:49 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/07 13:48:27 by gadeneux         ###   ########.fr       */
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
	*ret = 0;
	// ft_replace_env(data, *str);
	*list = ft_read_line(*str, ret);
	if (*ret != READ_OK)
		return (ft_put_error(GENERIC_ERROR, "Reading line error"));
	ft_expension_on_command(data, *list);
	return (0);
}

void	ft_run_line(char **str, t_data **data)
{
	int		ret;
	int		res_parse_line;
	t_elem	*list;

	res_parse_line = ft_parse_line(data, str, &ret, &list);
	if (res_parse_line == 0 && ft_pipe_is_present_on_line(list) == 0)
		g_status_minishell.status = 2;
	else
		g_status_minishell.status = 1;
	if (res_parse_line == 0)
	{
		if (ft_check_syntaxe_operator(list) == 0)
		{
			ft_redirection_open_all(data, list);
			if (list && list->str) // ft_strcmp(list->str, "") != 0
				ft_execute_command(data, list, (*data)->envp);
		}
		ft_free_elem(&list);
	}
}
