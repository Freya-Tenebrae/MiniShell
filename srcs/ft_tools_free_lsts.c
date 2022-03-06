/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_free_lsts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/06 14:48:22 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	ft_free_elem(t_elem **elem)
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
			if ((*elem)->in_content != NULL)
				free((*elem)->in_content);
			free(*elem);
			*elem = elem_ptr;
		}
	}
}

void	ft_free_output(t_output **output)
{
	if (output && output != NULL && *output != NULL)
	{
		if ((*output)->output != NULL)
			free((*output)->output);
		if ((*output)->error != NULL)
			free((*output)->error);
		free(*output);
	}
}

void	ft_free_env(t_env **env)
{
	if (env && env != NULL && *env != NULL)
	{
		if ((*env)->value && (*env)->value != NULL)
			free((*env)->value);
		if ((*env)->value && (*env)->name != NULL)
			free((*env)->name);
		free(*env);
	}
}

void	ft_free_data(t_data **data)
{
	int	i;

	if (data != NULL && *data != NULL)
	{
		if ((*data)->env != NULL)
		{
			i = 0;
			while ((*data)->env[i] != NULL)
				ft_free_env(&((*data)->env[i++]));
			free((*data)->env);
		}
		if ((*data)->envp != NULL)
			ft_freestrs(&((*data)->envp));
	}
	free(*data);
}
