/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:45:08 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/10 18:11:37 by cmaginot         ###   ########.fr       */
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

int	ft_redirection_out(t_elem *list)
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
			ft_open_fd(&fd, file_out, is_double_out);
			free(file_out);
			if (fd == -1)
				return (-1);
		}
		list = list->next;
	}
	return (fd);
}

void	ft_redirection_in(t_elem *list, char **file_in, int *is_double_in)
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
			if (*file_in != NULL)
				free(file_in);
			list = list->next;
			*file_in = ft_strdup(list->str);
			if (*file_in == NULL)
				ft_put_error(GENERIC_ERROR, "malloc error");
		}
		list = list->next;
	}
}

void	ft_in_on_infile(char *file_in, int is_double_in, char **infile)
{
	int	fd;

	if (is_double_in == 0)
	{
		fd = open(file_in, O_RDONLY);
		if (fd != -1)
		{
			if (ft_put_file_in_str(fd, infile) != 0)
				*infile = NULL;
		}
		else
			*infile = NULL;
	}
	else if (is_double_in == 1)
	{
		if (ft_put_double_in_str(file_in, infile) != 0)
			*infile = NULL;
	}
}
