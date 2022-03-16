/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_tools_redirections_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:39:16 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 13:39:43 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_elem_clone_left2(t_elem *cursor, t_elem *res)
{
	if (cursor->in_content)
	{
		res->in_content = ft_strdup(cursor->in_content);
		if (!res->in_content || res->in_content == NULL)
		{
			ft_put_error_null(GENERIC_ERROR, "malloc error");
			return (-1);
		}
	}
	else
		res->in_content = NULL;
	if (cursor->next && cursor->next->type != PIPE)
		res->next = ft_elem_clone_left(cursor->next);
	else
		res->next = 0;
	return (0);
}

t_elem	*ft_elem_clone_left(t_elem *cursor)
{
	t_elem		*res;

	res = malloc(sizeof(t_elem));
	if (!res)
		return (NULL);
	res->type = cursor->type;
	if (cursor->str)
	{
		res->str = ft_strdup(cursor->str);
		if (!res->str || res->str == NULL)
			return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	}
	else
		res->str = NULL;
	res->out_fd = cursor->out_fd;
	if (ft_elem_clone_left2(cursor, res) == -1)
		return (NULL);
	return (res);
}
