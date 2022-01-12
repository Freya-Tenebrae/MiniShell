/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/12 17:26:57 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* (Fonction test) Éxecute la prochaine à partir de l'élement spécifié */
/* Ne marche que pour les pipes sans gérer aucune exception. */
/* Cette ici que nous allons gérer les redirections, les build-in, les pipes etc. */

t_elem	*ft_runcmd_next(t_elem *elem, char **infile)
{
	char	**cmd_args;
	t_elem	*cur;
	t_output *out;
	int		len;
	int		i;
	
	cmd_args = 0;
	while (elem && elem->type != ARGUMENT)
		elem = elem->next;
	len = 0;
	cur = elem;
	while (cur && cur->type == ARGUMENT)
	{
		len++;
		cur = cur->next;
	}
	cmd_args = malloc(sizeof(char *) * (len + 1));
	if (!cmd_args)
		return (0);
	i = 0;
	while (elem && elem->type == ARGUMENT)
	{
		cmd_args[i] = ft_strdup(elem->str);
		elem = elem->next;
		i++;
	}
	cmd_args[i] = NULL;
	out = ft_run_cmd(minishell->path, cmd_args, *infile);
	free(cmd_args);
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
	*infile = out->output;
	return (elem);
}
