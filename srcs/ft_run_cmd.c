/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/23 20:14:55 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_lenght_args(t_elem *list)
{
	int		i;
	t_elem	*pos_list;

	i = 0;
	pos_list = list;
	while (pos_list && pos_list->type == ARGUMENT)
	{
		i++;
		pos_list = pos_list->next;
	}
	if (pos_list && (pos_list->type == IN || pos_list->type == DOUBLE_IN))
		return (i + 1);
	else
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
	while (list && list->type == ARGUMENT)
	{
		(*cmd_args)[i] = ft_strdup(list->str);
		list = list->next;
		i++;
	}
	if (list && (list->type == IN || list->type == DOUBLE_IN))
	{
		if (list->type == IN)
			(*cmd_args)[i] = ft_tools_get_in(list->str);
		else
			(*cmd_args)[i] = ft_tools_get_double_in(list->str);
		list = list->next;
		i++;
	}
	(*cmd_args)[i] = NULL;
	return (list);
}

static void	ft_redirection_cmd(t_output	**out, t_elem **list, char **infile)
{
	char		**cmd_args;

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

	ft_redirection_cmd(&out, &list, infile);
	free(*infile);
	if (out->output)
	{
		ft_putstr_fd(out->output, STDOUT_FILENO);
		*infile = ft_strdup(out->output);
		if (!infile)
		{
			infile = NULL;
			return (NULL);
		}
	}
	else
	{
		ft_putstr_fd(out->error, STDOUT_FILENO);
		infile = NULL;
	}
	ft_tools_free_output(&out);
	return (list);
}
