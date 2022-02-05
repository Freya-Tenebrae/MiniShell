/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:59:59 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/05 17:10:24 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_loop_read_line(int *i, char *str, char **buffer, t_elem **list)
{
	*i = ft_read_cmd(str, *i, buffer);
	if (*i < 0)
	{
		if (*buffer && *buffer != NULL)
			free(*buffer);
		ft_free_elem(list);
		return (-42);
	}
	else
	{
		if (*buffer == NULL)
		{
			ft_free_elem(list);
			return (-42);
		}
		if (ft_elem_add(list, *buffer) == -1)
		{
			free(*buffer);
			ft_free_elem(list);
			return (-42);
		}
		*buffer = NULL;
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
			return (NULL);
	}
	*ret = READ_OK;
	return (list);
}
