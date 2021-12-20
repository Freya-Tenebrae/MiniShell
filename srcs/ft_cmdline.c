/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2021/12/20 02:11:54 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

t_elem	*ft_runcmd_next(t_elem *elem, char **envp, char **infile)
{
	char **cmd_args = 0;
	
	// Skip until argument
	while (elem && elem->type != ARGUMENT)
		elem = elem->next;
	
	int len = 0;
	t_elem *cur = elem;
	while (cur && cur->type == ARGUMENT)
	{
		len++;
		cur = cur->next;
	}
	
	cmd_args = malloc(sizeof(char*) * (len + 1));
	if (!cmd_args)
		return (0);
		
	int i = 0;
	while (elem && elem->type == ARGUMENT)
	{
		cmd_args[i] = ft_strdup(elem->str);
		elem = elem->next;
		i++;
	}
	cmd_args[i] = NULL;
	char *out = ft_runcmd(ft_getpath(envp), cmd_args, *infile);
	printf("%s", out);
	free(cmd_args);
	free(*infile);
	*infile = out;
	return (elem);
}
