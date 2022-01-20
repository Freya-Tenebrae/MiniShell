/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/20 18:02:43 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* (Fonction test) Éxecute la prochaine à partir de l'élement spécifié */
/* Ne marche que pour les pipes sans gérer aucune exception. */
/* Cette ici que nous allons gérer les redirections, les build-in, les pipes etc. */

static int	ft_lenght_args(t_elem *list)
{
	int		i;
	t_elem *pos_list;

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
		return (0);
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
		i++;
	}
	(*cmd_args)[i] = NULL;
	return (list);
}

t_elem	*ft_runcmd_next(t_elem *list, char **infile)
{
	char	**cmd_args;
	t_output *out;

	list = ft_put_args_in_cmd_args(list, &cmd_args);
	out = ft_run_cmd(minishell->path, cmd_args, *infile);
	ft_freestrs(&cmd_args);
	free(*infile);
	if (out->output)
		ft_putstr_fd(out->output, STDOUT_FILENO);
	else
		ft_putstr_fd(out->error, STDOUT_FILENO);
	if (out->error)
	{
		*infile = 0;
		return (0);
	}
	*infile = ft_strdup(out->output);
	ft_tools_free_output(&out);
	return (list);
}
