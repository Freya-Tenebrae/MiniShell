/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/01 19:46:23 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_redirection_out(t_elem *list, char **file_out)
{
	*file_out = NULL;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == OUT || list->type == DOUBLE_OUT)
		{
			list = list->next;
			// si le fichier n'existe pas, le creer
			if (list->type == OUT)
				; // vider le contenu du fichier
			if (*file_out != NULL)
				free(file_out);
			*file_out = ft_strdup(list->str);
			if (*file_out == NULL)
				ft_tools_put_error(GENERIC_ERROR, "malloc error");
		}
		list = list->next;
	}
}

static void	ft_redirection_in(t_elem *list, char **file_in, int *is_double_in)
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
				ft_tools_put_error(GENERIC_ERROR, "malloc error");
		}
		list = list->next;
	}
}

static void	ft_in_on_infile(char *file_in, int is_double_in, char **infile)
{
	int	fd;

	if (*infile != NULL)
		free(infile);
	if (is_double_in == 0)
	{
		fd = open(file_in, O_RDONLY);
		if (fd != -1)
		{
			if (ft_tools_put_file_in_str(fd, infile) != 0)
				*infile = NULL;
		}
		else
			*infile = NULL;
	}
	else if (is_double_in == 1)
	{
		if (ft_tools_put_double_in_str(file_in, infile) != 0)
			*infile = NULL;
	}
}

static int	ft_lenght_args(t_elem *list)
{
	int		i;

	i = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN || \
			list->type == OUT || list->type == DOUBLE_OUT)
			list = list->next->next;
		else
		{
			i++;
			list = list->next;
		}
	}
	return (i);
}

static t_elem	*ft_put_args_in_cmd_args(t_elem *list, char ***cmd_args)
{
	int		i;

	i = ft_lenght_args(list);
	*cmd_args = malloc(sizeof(char *) * (i + 1));
	if (!*cmd_args)
		return (NULL);
	i = 0;
	while (list != NULL && list->type != PIPE)
	{
		if (list->type == IN || list->type == DOUBLE_IN || \
			list->type == OUT || list->type == DOUBLE_OUT)
			list = list->next->next;
		else
		{
			(*cmd_args)[i++] = ft_strdup(list->str);
			if ((*cmd_args)[i - 1] == NULL)
			{
				ft_tools_put_error(GENERIC_ERROR, "malloc error");
				return (NULL);
			}
			list = list->next;
		}
	}
	(*cmd_args)[i] = NULL;
	return (list);
}

static void	ft_redirection_cmd(t_output	**out, t_elem **list, char **infile)
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
		*out = ft_run_bi(g_minishell->path, cmd_args, *infile);
	else
		*out = ft_exec_cmd(g_minishell->path, cmd_args, *infile);
	ft_freestrs(&cmd_args);
}

t_elem	*ft_run_cmd(t_elem *list, char **infile)
{
	t_output	*out;
	char		*file_out;
	int			fd;

	ft_redirection_out(list, &file_out);
	ft_redirection_cmd(&out, &list, infile);
	free(*infile);
	*infile = NULL;
	if (out == NULL)
	{
		ft_tools_put_error(GENERIC_ERROR, "output error");
		return (NULL);
	}
	if (out->output == NULL && out->error == NULL)
	{
		ft_tools_put_error(GENERIC_ERROR, "output error");
		ft_tools_free_output(&out);
		return (NULL);
	}
	if (out->output != NULL)
	{
		if (file_out != NULL)
		{
			(void) fd;
			// open file_out et mettre le fd dans une variable fd
			// ft_putstr_fd(out->output, fd);
		}
		if (list == NULL)
		{
			ft_putstr_fd(out->output, STDOUT_FILENO);
		}
		else if (list->type == PIPE)
		{
			*infile = ft_strdup(out->output);
			list = list->next;
			if (!*infile)
			{
				ft_tools_put_error(GENERIC_ERROR, "malloc error");
				ft_tools_free_output(&out);
				return (NULL);
			}
		}
	}
	else
	{
		ft_putstr_fd(out->error, STDOUT_FILENO);
		*infile = ft_strdup("");
		if (list != NULL && list->type == PIPE)
			list = list->next;
	}
	ft_tools_free_output(&out);
	return (list);
}
