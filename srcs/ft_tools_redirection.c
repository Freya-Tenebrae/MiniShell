/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:45:08 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/25 06:14:19 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int ft_redirection_in_present(t_elem *list)
{
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN)
			return (1);
		list = list->next;
	}
	return (0);
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
			if (ft_strlen(file_out) > 255)
			{
				ft_put_error(FILENAME_TOO_LONG_ERROR, file_out);
				free(file_out);
				return (-1);
			}
			ft_open_fd(&fd, file_out, is_double_out);
			free(file_out);
			if (fd == -1)
				return (-1);
		}
		list = list->next;
	}
	return (fd);
}

int	ft_redirection_in(t_elem *list, char **file_in, int *is_double_in)
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

int	ft_in_on_infile(char *file_in, int is_double_in, char **infile)
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
		{
			*infile = NULL;
			return (ft_put_error(GENERIC_ERROR, "file can't be oppened"));
		}
	}
	else if (is_double_in == 1)
	{
		if (ft_put_double_in_str(file_in, infile) != 0)
			*infile = NULL;
	}
	return (0);
}

static void	ft_fill_stdin(char *infile)
{
	int	input[2];
	int	pid2;

	if (infile != NULL)
	{
		if (pipe(input) == -1)
			exit(0);
		pid2 = fork();
		if (pid2 == 0)
		{
			ft_putstr_fd(infile, input[1]);
			exit(0);
		}
		close(input[1]);
		waitpid(pid2, 0, 0);
		dup2(input[0], STDIN_FILENO);
		close(input[0]);
	}
}

static void	ft_fill_file_by_stdout(int fd)
{
	int	input[2];
	int	pid2;

	(void)fd;

	if (pipe(input) == -1)
		exit(0);
	pid2 = fork();
	if (pid2 == 0)
	{
		ft_putstr_fd("", input[0]);
		exit(0);
	}
	close(input[0]);
	waitpid(pid2, 0, 0);
	dup2(input[1], STDOUT_FILENO);
	close(input[0]);
}

int	ft_replace_in_by_redirection_out(t_elem *list)
{
	int		fd;

	fd = ft_redirection_out(list);
	if (fd == -1)
		return (-1);
	if (fd == 0)
		return (0);
	ft_fill_file_by_stdout(fd);
	return (0);
}

int	ft_replace_in_by_redirection_in(t_elem *list)
{
	char	*file_in;
	char	*infile;
	int		is_double_in;

	file_in = NULL;
	infile = NULL;
	is_double_in = 0;
	if (ft_redirection_in(list, &file_in, &is_double_in) == -1)
		return (-1);
	if (is_double_in == 1)
		; // put something to lock exec in this fork
	if (ft_in_on_infile(file_in, is_double_in, &infile) == -1)
		return (-1);
	ft_fill_stdin(infile);
	return (0);
}
