/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_tools_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:47:43 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/28 15:37:27 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_elem_is_redirection(t_elem *elem)
{
	return (elem->type == IN || elem->type == DOUBLE_IN || elem->type == OUT || elem->type == DOUBLE_OUT);
}

int	ft_elem_get_cmd_args_count(t_elem *cursor)
{
	int		i;

	i = 0;
	while (cursor)
	{
		if (cursor->type == PIPE)
			break ;
		if (ft_elem_is_redirection(cursor))
		{
			cursor = cursor->next->next;
			continue ;
		}
		cursor = cursor->next;
		i++;
	}
	return (i);
}

char	**ft_elem_get_cmd_args(t_data **data, t_elem *cursor)
{
	char	**cmd_tab;
	int		i;

	(void) data;
	i = 0;
	cmd_tab = malloc(sizeof(char*) * (ft_elem_get_cmd_args_count(cursor) + 1));
	if (!cmd_tab)
		return (0);
	while (cursor)
	{
		if (cursor->type == PIPE)
			break ;
		if (ft_elem_is_redirection(cursor))
		{
			cursor = cursor->next->next;
			continue ;
		}
		cmd_tab[i] = cursor->str;
		cursor = cursor->next;
		i++;
	}
	cmd_tab[i] = 0;
	return (cmd_tab);
}

t_elem	*ft_elem_get_right(t_elem *cursor)
{
	while (cursor)
	{
		if (cursor->type == PIPE)
			return (cursor->next);
		cursor = cursor->next;
	}
	return (0);
}

t_elem	*ft_elem_clone_left(t_elem *cursor)
{
	t_elem		*res;

	res = malloc(sizeof(t_elem));
	if (!res)
		return (0);
	res->type = cursor->type;
	res->str = ft_strdup(cursor->str);
	res->out_fd = cursor->out_fd;
	if (cursor->in_content)
		res->in_content = ft_strdup(cursor->in_content);
	else
		res->in_content = NULL;
	if (cursor->next && cursor->next->type != PIPE)
		res->next = ft_elem_clone_left(cursor->next);
	else
		res->next = 0;
	return (res);
}