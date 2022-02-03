/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/03 17:55:24 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_redirection_cmd(t_data **g_minishell, t_output **out, \
												t_elem **list, char **infile)
{
	char	*file_in;
	int		is_double_in;
	char	**cmd_args;

	ft_redirection_in(*list, &file_in, &is_double_in);
	if (file_in != NULL)
	{
		ft_in_on_infile(file_in, is_double_in, infile);
		free(file_in);
	}
	*list = ft_put_args_in_cmd_args(*list, &cmd_args);
	if (ft_tools_is_build_in(cmd_args[0]) == 0)
		*out = ft_run_bi((*g_minishell)->path, cmd_args, *infile);
	else
		*out = ft_exec_cmd((*g_minishell)->path, cmd_args, *infile);
	ft_freestrs(&cmd_args);
}

static int	ft_init_run_cmd(t_elem *list, int *fd, char **infile)
{
	*fd = ft_redirection_out(list);
	if (*fd == -1)
	{
		ft_tools_put_error(GENERIC_ERROR, \
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

static int	ft_check_error_output_run_cmd(t_output **out)
{
	if (*out == NULL)
	{
		ft_tools_put_error(GENERIC_ERROR, "output error");
		return (-1);
	}
	if ((*out)->output == NULL && (*out)->error == NULL)
	{
		ft_tools_put_error(GENERIC_ERROR, "output error");
		ft_tools_free_output(out);
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
	if (fd != 0)
	{
		ft_putstr_fd((*out)->output, fd);
		close(fd);
	}
	if (*list != NULL && (*list)->type == PIPE)
	{
		*infile = ft_strdup((*out)->output);
		(*list) = (*list)->next;
		if (!*infile)
		{
			ft_tools_put_error(GENERIC_ERROR, "malloc error");
			ft_tools_free_output(out);
			return (-1);
		}
	}
	return (0);
}

t_elem	*ft_run_cmd(t_data **g_minishell, t_elem *list, char **infile)
{
	t_output	*out;
	int			fd;

	if (ft_init_run_cmd(list, &fd, infile) != 0)
		return (NULL);
	ft_redirection_cmd(g_minishell, &out, &list, infile);
	free(*infile);
	*infile = NULL;
	if (ft_check_error_output_run_cmd(&out) != 0)
		return (NULL);
	if (out->output != NULL)
	{
		if (ft_manage_correct_output_run_cmd(&out, &list, fd, infile) != 0)
			return (NULL);
	}
	else
	{
		ft_putstr_fd(out->error, STDERR_FILENO);
		*infile = ft_strdup("");
		if (list != NULL && list->type == PIPE)
			list = list->next;
	}
	ft_tools_free_output(&out);
	return (list);
}
