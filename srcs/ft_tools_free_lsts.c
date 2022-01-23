/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_free_lsts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/23 19:07:20 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	ft_tools_free_elem(t_elem **elem)
{
	t_elem	*elem_ptr;

	if (elem && *elem)
	{
		elem_ptr = *elem;
		while (elem_ptr != NULL)
		{
			elem_ptr = elem_ptr->next;
			if ((*elem)->str != NULL)
				free((*elem)->str);
			free(*elem);
			*elem = elem_ptr;
		}
	}
}

void	ft_tools_free_output(t_output **output)
{
	if (output != NULL && *output != NULL)
	{
		if ((*output)->output != NULL)
			free((*output)->output);
		if ((*output)->error != NULL)
			free((*output)->error);
		free(*output);
	}
}

void	ft_tools_free_env(t_env **env)
{
	if (env != NULL && *env != NULL)
	{
		if ((*env)->value != NULL)
			free((*env)->value);
		if ((*env)->name != NULL)
			free((*env)->name);
		free(*env);
	}
}

void	ft_tools_free_data(t_data **data)
{
	if (data != NULL && *data != NULL)
	{
		ft_tools_free_env((*data)->env);
		if ((*data)->path != NULL)
			free((*data)->path);
	}
}
