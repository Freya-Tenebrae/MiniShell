/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_syntaxe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:12:00 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/17 02:08:49 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_check_syntaxe_operator(t_elem *list)
{
	t_elem	*list_ptr;

	list_ptr = NULL;
	while (list != NULL)
	{
		if (list->type == -1)
			return (-1);
		if (list->type == PIPE && \
			(list_ptr == NULL || list_ptr->type != ARGUMENT))
			return (ft_put_error(OPERATOR_ERROR, list->str));
		else if ((list->type == OUT || list->type == DOUBLE_OUT || \
					list->type == IN || list->type == DOUBLE_IN) && \
					(list_ptr != NULL && list_ptr->type != PIPE && \
					list_ptr->type != ARGUMENT))
			return (ft_put_error(OPERATOR_ERROR, list->str));
		else if ((list->type == IN || list->type == DOUBLE_IN || \
			list->type == OUT || list->type == DOUBLE_OUT || \
			list->type == PIPE) && list->next == NULL)
			return (ft_put_error(OPERATOR_ERROR, "/n"));
		list_ptr = list;
		list = list->next;
	}
	return (0);
}
