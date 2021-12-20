/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmdline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2021/12/20 01:01:41 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

t_elem	*ft_runcmd_next(t_elem *elem, char **envp, char **infile)
{
	char *cmd = 0;
	
	// Skip until argument
	while (elem && elem->type != ARGUMENT)
		elem = elem->next;
		
	while (elem && elem->type == ARGUMENT)
	{
		ft_writestr_on(&cmd, elem->str);
		if (elem->next)
			ft_writechar_on(&cmd, (char) 32);
		elem = elem->next;
	}
	printf("Command: ~%s~\n", cmd);
	char *out = ft_runcmd(ft_getpath(envp), cmd, *infile);
	printf("\"%s\"\n", out);
	free(*infile);
	*infile = out;
	return (elem);
}
