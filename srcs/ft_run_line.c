/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:18:49 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/21 15:52:42 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static t_elem	*ft_clear_list_from_null_strat(t_elem **list)
{
	t_elem	*ptr_list;

	while (*list && *list != NULL)
	{
		if ((*list)->str != NULL)
			break ;
		ptr_list = *list;
		*list = (*list)->next;
		if (ptr_list->in_content != NULL)
			free(ptr_list->in_content);
		free(ptr_list);
	}
	return (*list);
}

static t_elem	*ft_clear_list_from_null(t_elem **list)
{
	t_elem	*ptr_list_1;
	t_elem	*ptr_list_2;
	t_elem	*ptr_list_3;

	*list = ft_clear_list_from_null_strat(list);
	ptr_list_2 = *list;
	while (ptr_list_2 != NULL && ptr_list_2->next != NULL)
	{
		ptr_list_1 = ptr_list_2->next;
		ptr_list_3 = ptr_list_1;
		if (ptr_list_1->str == NULL)
		{
			ptr_list_1 = ptr_list_1->next;
			ptr_list_2->next = ptr_list_1;
			if (ptr_list_3->in_content != NULL)
				free(ptr_list_3->in_content);
			free(ptr_list_3);
		}
		else
		{
			ptr_list_2 = ptr_list_1;
			ptr_list_1 = ptr_list_1->next;
		}
	}
	return (*list);
}

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
	{
		g_status_minishell.status_pipe = 258;
		return (ft_put_error(GENERIC_ERROR, "Quote error"));
	}
	*ret = 0;
	*list = ft_read_line(*str, ret);
	if (*ret != READ_OK)
		return (ft_put_error(GENERIC_ERROR, "Reading line error"));
	if (ft_check_syntaxe_operator(*list) != 0)
		return (-2);
	ft_expension_on_command(data, *list);
	*list = ft_clear_list_from_null(list);
	return (0);
}

void	ft_run_line(char **str, t_data **data)
{
	int		ret;
	int		res_parse_line;
	t_elem	*list;

	res_parse_line = ft_parse_line(data, str, &ret, &list);
	if (res_parse_line == 0 && ft_pipe_is_present_on_line(list) == 0)
		g_status_minishell.status_minishell = 2;
	else
		g_status_minishell.status_minishell = 1;
	if (res_parse_line == -2)
		ft_free_elem(&list);
	if (res_parse_line == 0)
	{
		if (ft_redirection_open_all(data, list) != 0)
		{
			if (list && list->str)
				ft_execute_command(data, list);
			else
				g_status_minishell.status_pipe = 0;
		}
		ft_free_elem(&list);
	}
}
