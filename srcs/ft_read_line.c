/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:59:59 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/10 17:36:42 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_put_in_list(char **buffer, t_elem **list, int is_operator)
{
	if (*buffer == NULL)
	{
		ft_free_elem(list);
		return (-42);
	}
	if (ft_elem_add(list, *buffer, is_operator) == -1)
	{
		free(*buffer);
		*buffer = NULL;
		ft_free_elem(list);
		return (-42);
	}
	*buffer = NULL;
	return (0);
}

static int	ft_loop_read_line(int *i, char *str, char **buffer, t_elem **list)
{
	int	is_operator;

	is_operator = 1;
	*i = ft_read_cmd(str, *i, buffer, &is_operator);
	if (*i < 0)
	{
		if (*buffer && *buffer != NULL)
			free(*buffer);
		ft_free_elem(list);
		return (-42);
	}
	else
	{
		if (ft_put_in_list(buffer, list, is_operator) == -42)
			return (-42);
	}
	return (*i);
}

t_elem	*ft_read_line(char *str, int *ret)
{
	int		i;
	int		strlen;
	char	*buffer;
	t_elem	*list;

	if (!str || str == NULL)
		return (NULL);
	i = 0;
	buffer = NULL;
	list = NULL;
	strlen = ft_strlen(str);
	i = 0;
	while (i >= 0 && i < strlen)
	{
		*ret = ft_loop_read_line(&i, str, &buffer, &list);
		if (i == -42)
		{
			return (NULL);
		}
	}
	*ret = READ_OK;
	return (list);
}
