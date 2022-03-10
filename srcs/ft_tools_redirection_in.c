/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_redirection_in.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:45:08 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/10 10:52:51 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_redirection_in(t_elem *list, char **file_in)
{
	*file_in = NULL;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN)
		{
			list = list->next;
			if (*file_in)
				free(*file_in);
			*file_in = ft_strdup(list->str);
			if (!*file_in || *file_in == NULL)
				return (ft_put_error(GENERIC_ERROR, "malloc error"));
		}
		list = list->next;
	}
	return (0);
}

int	ft_redirection_get_fd_in(t_elem *list)
{
	char	*file_in;
	char	*infile;
	int		is_double_in;
	int		fd;

	file_in = NULL;
	infile = NULL;
	is_double_in = 0;
	if (ft_redirection_in(list, &file_in) == -1)
	{
		if (file_in)
			free(file_in);
		return (-1);
	}
	fd = open(file_in, O_RDONLY);
	if (file_in)
		free(file_in);
	return (fd);
}

// char	*ft_redirection_get_double_in_fd(t_elem *list)
// {
// 	char	*res;

// 	res = 0;
// 	while (list != NULL && list->type != PIPE)
// 	{
// 		if (list->type == DOUBLE_IN)
// 			res = list->next->str;
// 		list = list->next;
// 	}
// 	return (res);
// }

int	ft_redirection_in_present(t_elem *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN)
			return (1);
		list = list->next;
	}
	return (0);
}
