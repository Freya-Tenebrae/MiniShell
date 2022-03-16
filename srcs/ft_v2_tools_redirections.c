/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_tools_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:47:43 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 13:39:39 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_elem_is_redirection(t_elem *elem)
{
	return (elem->type == IN || elem->type == DOUBLE_IN || \
		elem->type == OUT || elem->type == DOUBLE_OUT);
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
		if (cursor->str == NULL)
		{
			cursor = cursor->next;
			continue ;
		}
		i++;
		cursor = cursor->next;
	}
	return (i);
}

void	ft_elem_get_cmd_args2(t_elem *cursor, char **cmd_tab)
{
	int	i;

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
		if (cursor->str == NULL)
		{
			cursor = cursor->next;
			continue ;
		}
		cmd_tab[i] = cursor->str;
		cursor = cursor->next;
		i++;
	}
	cmd_tab[i] = 0;
}

char	**ft_elem_get_cmd_args(t_data **data, t_elem *cursor)
{
	char	**cmd_tab;
	int		i;

	(void) data;
	i = 0;
	cmd_tab = malloc(sizeof(char *) * (ft_elem_get_cmd_args_count(cursor) + 1));
	if (!cmd_tab)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	ft_elem_get_cmd_args2(cursor, cmd_tab);
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
