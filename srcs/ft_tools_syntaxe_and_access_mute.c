/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_syntaxe_and_access_mute.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:12:00 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/16 14:04:42 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_check_access_ok_mute_in_loop_is_dir(t_elem **list)
{
	struct stat	*statbuf;

	ft_put_error(GENERIC_ERROR, (*list)->str);
	statbuf = malloc(sizeof(struct stat));
	if (!statbuf || statbuf == NULL)
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	stat((*list)->str, statbuf);
	if ((statbuf->st_mode & S_IFMT) == S_IFDIR)
	{
		free(statbuf);
		return (-1);
	}
	else
	{
		free(statbuf);
		return (0);
	}
}

static int	ft_check_access_ok_mute_in_loop(t_elem **list)
{
	if ((*list)->type == IN || (*list)->type == OUT || \
													(*list)->type == DOUBLE_OUT)
	{
		*list = (*list)->next;
		if (access((*list)->str, F_OK) != 0)
			return (-1);
		else if (access((*list)->str, R_OK) != 0)
			return (-1);
		else if (ft_check_access_ok_mute_in_loop_is_dir(list) != 0)
			return (-1);
	}
	return (0);
}

int	ft_check_one_access_ok_mute(t_elem *list)
{
	if (list != NULL && list->type == PIPE)
		list = list->next;
	while (list != NULL && list->type != PIPE)
	{
		if (ft_check_access_ok_mute_in_loop(&list) == -1)
		{
			g_status_minishell.status_pipe = 1;
			return (-1);
		}
		list = list->next;
	}
	return (0);
}
