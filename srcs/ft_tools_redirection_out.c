/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_redirection_out.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:45:08 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/17 12:30:56 by cmaginot         ###   ########.fr       */
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

static int	ft_redirection_out(t_elem *list, int *is_double_out, int *fd)
{
	char	*file_out;

	file_out = NULL;
	*is_double_out = 0;
	if (list->type == DOUBLE_OUT)
		*is_double_out = 1;
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
	if (*fd != 0)
		close(*fd);
	ft_open_fd(fd, file_out, *is_double_out);
	free(file_out);
	if (*fd == -1)
		return (-1);
	return (0);
}

int	ft_redirection_get_fd_out(t_elem *list)
{
	int		is_double_out;
	int		fd;

	fd = 0;
	is_double_out = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (ft_check_access_out_ok_mute(list) != 0)
			return (-1);
		if (list->type == OUT || list->type == DOUBLE_OUT)
		{
			if (fd > 1)
				close (fd);
			ft_redirection_out(list, &is_double_out, &fd);
		}
		list = list->next;
	}
	return (fd);
}

int	ft_redirection_out_present(t_elem *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == OUT || list->type == DOUBLE_OUT)
			return (1);
		list = list->next;
	}
	return (0);
}
