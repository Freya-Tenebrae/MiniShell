/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_syntaxe_and_access.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:12:00 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/10 18:10:23 by cmaginot         ###   ########.fr       */
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

void	ft_check_access_ok_speak_only(t_elem *list)
{
	if (list != NULL && list->type == PIPE)
		list = list->next;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN)
		{
			list = list->next;
			if (access(list->str, F_OK) != 0)
				ft_put_error(FILE_ERROR, list->str);
			else if (access(list->str, R_OK) != 0)
				ft_put_error(ACCESS_ERROR, list->str);
		}
		if (list->type == OUT || list->type == DOUBLE_OUT)
		{
			list = list->next;
			if (access(list->str, F_OK) == 0)
			{
				if (access(list->str, W_OK) != 0)
					ft_put_error(ACCESS_ERROR, list->str);
			}
		}
		list = list->next;
	}
}

int	ft_check_access_ok_mute(t_elem *list)
{
	if (list != NULL && list->type == PIPE)
		list = list->next;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN)
		{
			list = list->next;
			if (access(list->str, F_OK) != 0)
				return (-1);
			else if (access(list->str, R_OK) != 0)
				return (-1);
		}
		if (list->type == OUT || list->type == DOUBLE_OUT)
		{
			list = list->next;
			if (access(list->str, F_OK) == 0)
			{
				if (access(list->str, W_OK) != 0)
					return (-1);
			}
		}
		list = list->next;
	}
	return (0);
}

int	ft_check_one_access_ok_mute(t_elem *list)
{
	if (list->type == IN)
	{
		list = list->next;
		if (access(list->str, F_OK) != 0)
			return (-1);
		else if (access(list->str, R_OK) != 0)
			return (-1);
	}
	if (list->type == OUT || list->type == DOUBLE_OUT)
	{
		list = list->next;
		if (access(list->str, F_OK) == 0)
		{
			if (access(list->str, W_OK) != 0)
				return (-1);
		}
	}
	return (0);
}
