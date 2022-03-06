/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_arguments_to_strs.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:48:13 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/06 10:27:41 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_lenght_args(t_elem *list)
{
	int		i;

	i = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN || \
			list->type == OUT || list->type == DOUBLE_OUT)
			list = list->next->next;
		else
		{
			i++;
			list = list->next;
		}
	}
	return (i);
}

t_elem	*ft_put_args_in_cmd_args(t_elem *list, char ***cmd_args)
{
	int		i;

	i = ft_lenght_args(list);
	*cmd_args = malloc(sizeof(char *) * (i + 1));
	if (!*cmd_args)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	i = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN || \
			list->type == OUT || list->type == DOUBLE_OUT)
			list = list->next->next;
		else
		{
			(*cmd_args)[i++] = ft_strdup(list->str);
			if (!(*cmd_args)[i - 1] || (*cmd_args)[i - 1] == NULL)
				return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
			list = list->next;
		}
	}
	(*cmd_args)[i] = NULL;
	return (list);
}
