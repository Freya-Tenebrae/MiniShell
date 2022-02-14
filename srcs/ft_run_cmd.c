/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/14 07:31:24 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_redirection_cmd(t_data **data, t_output **out, \
												t_elem **list, char **infile)
{
	char	*file_in;
	int		is_double_in;
	char	**cmd_args;

	ft_redirection_in(*list, &file_in, &is_double_in);
	if (file_in != NULL)
	{
		if (*infile && *infile != NULL)
			free(*infile);
		*infile = NULL;
		ft_in_on_infile(file_in, is_double_in, infile);
		free(file_in);
	}
	*list = ft_put_args_in_cmd_args(*list, &cmd_args);
	if (!cmd_args || cmd_args == NULL)
	{
		*out = NULL;
		return ;
	}
	if (ft_is_build_in(cmd_args[0]) == 0)
		*out = ft_run_bi(data, (*data)->path, cmd_args, *infile);
	else
		*out = ft_exec_cmd((*data)->path, cmd_args, *infile);
	ft_freestrs(&cmd_args);
}

static int	ft_init_run_cmd(t_elem **list, int *fd, char **infile)
{
	if (ft_check_access_ok(*list) != 0)
	{
		if ((*list)->type == PIPE)
			*list = (*list)->next;
		while (*list != NULL && (*list)->type != PIPE)
			*list = (*list)->next;
		return (0);
	}
	*fd = ft_redirection_out(*list);
	if (*fd == -1)
	{
		ft_put_error(GENERIC_ERROR, \
							"redirection out error, file can't be oppened");
		if (*infile != NULL)
		{
			free(*infile);
			*infile = NULL;
		}
		return (-1);
	}
	return (0);
}

static int	ft_manage_correct_output_run_cmd(t_output **out, \
										t_elem **list, int fd, char **infile)
{
	if (*list == NULL && fd == 0)
	{
		ft_putstr_fd((*out)->output, STDOUT_FILENO);
	}
	else
	{
		if (fd != 0)
		{
			ft_putstr_fd((*out)->output, fd);
			*infile = ft_strdup((*out)->output);
			close(fd);
		}
		else if (*list != NULL && (*list)->type == PIPE)
		{
			*infile = ft_strdup((*out)->output);
			(*list) = (*list)->next;
		}
		if (!*infile)
		{
			ft_free_output(out);
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		}
	}
	return (0);
}

static int	ft_check_error_and_exec_correct_output(t_output **out, \
										t_elem **list, int fd, char **infile)
{
	if (*out == NULL)
	{
		ft_put_error(GENERIC_ERROR, "output error");
		return (-1);
	}
	if ((*out)->output == NULL && (*out)->error == NULL)
	{
		ft_put_error(GENERIC_ERROR, "output error");
		ft_free_output(out);
		return (-1);
	}
	if ((*out)->output != NULL)
	{
		if (ft_manage_correct_output_run_cmd(out, list, fd, infile) != 0)
			return (-1);
		return (0);
	}
	return (1);
}

t_elem	*ft_run_cmd(t_data **data, t_elem *list, char **infile)
{
	t_output	*out;
	int			fd;
	int			i;

	if (ft_init_run_cmd(&list, &fd, infile) != 0)
		return (NULL);
	ft_redirection_cmd(data, &out, &list, infile);
	free(*infile);
	*infile = NULL;
	i = ft_check_error_and_exec_correct_output(&out, &list, fd, infile);
	if (i == -1)
		return (NULL);
	else if (i == 1)
	{
		if (out->error != NULL)
			ft_putstr_fd(out->error, STDERR_FILENO);
		else
		{
			ft_put_error(GENERIC_ERROR, "error output error");
			return (NULL);
		}
		*infile = ft_strdup("");
		if (!*infile || *infile == NULL)
		{
			ft_put_error(GENERIC_ERROR, "malloc error");
			ft_free_output(&out);
			return (NULL);
		}
		if (list != NULL && list->type == PIPE)
			list = list->next;
	}
	ft_free_output(&out);
	return (list);
}
