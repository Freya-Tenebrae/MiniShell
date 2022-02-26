/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:45:08 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/26 21:05:27 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_open_fd(int *fd, char *file_out, int is_double_out)
{
	if (*fd > 0)
		close(*fd);
	if (is_double_out == 1)
		*fd = open(file_out, O_WRONLY | O_APPEND | O_CREAT, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	else
		*fd = open(file_out, O_WRONLY | O_TRUNC | O_CREAT, \
							S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
}

static int	ft_redirection_out(t_elem *list)
{
	char	*file_out;
	int		is_double_out;
	int		fd;

	file_out = NULL;
	fd = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == OUT || list->type == DOUBLE_OUT)
		{
			is_double_out = 0;
			if (list->type == DOUBLE_OUT)
				is_double_out = 1;
			list = list->next;
			file_out = ft_strdup(list->str);
			if (file_out == NULL)
				return (ft_put_error(GENERIC_ERROR, "malloc error"));
			if (ft_strlen(file_out) > 255)
			{
				ft_put_error(FILENAME_TOO_LONG_ERROR, file_out);
				free(file_out);
				return (-1);
			}
			if (fd != 0)
				close(fd);
			ft_open_fd(&fd, file_out, is_double_out);
			free(file_out);
			if (fd == -1)
				return (-1);
		}
		list = list->next;
	}
	return (fd);
}

static int	ft_redirection_in(t_elem *list, char **file_in, int *is_double_in)
{
	*file_in = NULL;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN)
		{
			if (list->type == DOUBLE_IN)
				*is_double_in = 1;
			else
				*is_double_in = 0;
			list = list->next;
			*file_in = ft_strdup(list->str);
			if (!*file_in || *file_in == NULL)
				return(ft_put_error(GENERIC_ERROR, "malloc error"));
		}
		list = list->next;
	}
	return (0);
}

int	ft_get_fd_redirection_out(t_elem *list)
{
	int		fd;

	fd = ft_redirection_out(list);
	return (fd);
}

int	ft_get_fd_redirection_in(t_elem *list)
{
	char	*file_in;
	char	*infile;
	int		is_double_in;
	int		fd;

	file_in = NULL;
	infile = NULL;
	is_double_in = 0;
	if (ft_redirection_in(list, &file_in, &is_double_in) == -1)
		return (-1);
	fd = open(file_in, O_RDONLY);
	return (fd);
}

char *ft_get_fd_redirection_double_in(t_elem *list)
{
	char *res;

	res = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == DOUBLE_IN)
			res = list->next->str;
		list = list->next;
	}
	return (res);
}

int ft_redirection_double_in_present(t_elem *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == DOUBLE_IN)
			return (1);
		list = list->next;
	}
	return (0);
}

int ft_redirection_in_present(t_elem *list)
{
	int		res;

	res = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN)
		{
			res = 1;
			// Voir priorité en fonction de << et <
		}
		list = list->next;
	}
	return (res);
}

int ft_redirection_out_present(t_elem *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == OUT || list->type == DOUBLE_OUT)
			return (1);
		list = list->next;
	}
	return (0);
}