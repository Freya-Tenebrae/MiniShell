/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_tools_redirections.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:47:43 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/14 17:38:56 by gadeneux         ###   ########.fr       */
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
