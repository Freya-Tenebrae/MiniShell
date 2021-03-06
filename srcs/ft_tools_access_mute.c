/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_access_mute.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:12:00 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/21 16:21:16 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_check_access_ok_in_loop_is_dir_mute(t_elem **list)
{
	struct stat	*statbuf;

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

static int	ft_fcheck_access_ok_out_loop_mute_in(t_elem **list)
{
	*list = (*list)->next;
	if (!*list || *list == NULL || (*list)->type != ARGUMENT)
		return (-1);
	if (access((*list)->str, F_OK) != 0)
		return (-1);
	else if (access((*list)->str, R_OK) != 0)
		return (ft_put_error(ACCESS_ERROR, (*list)->str));
	else if (ft_check_access_ok_in_loop_is_dir_mute(list) != 0)
		return (-1);
	return (0);
}

static int	ft_check_access_ok_out_loop_mute(t_elem **list)
{
	if ((*list)->type == IN)
	{
		if (ft_fcheck_access_ok_out_loop_mute_in(list) == -1)
			return (-1);
	}
	if ((*list)->type == OUT || (*list)->type == DOUBLE_OUT)
	{
		*list = (*list)->next;
		if (!*list || *list == NULL || (*list)->type != ARGUMENT)
			return (-1);
		if (access((*list)->str, F_OK) == 0)
		{
			if (access((*list)->str, W_OK) != 0)
				return (ft_put_error(ACCESS_ERROR, (*list)->str));
			else if (ft_check_access_ok_in_loop_is_dir_mute(list) != 0)
				return (-1);
		}
	}
	return (0);
}

int	ft_check_access_out_ok_mute(t_elem *list)
{
	if (list != NULL && list->type == PIPE)
		list = list->next;
	if (list != NULL && list->type != PIPE)
	{
		if (ft_check_access_ok_out_loop_mute(&list) == -1)
		{
			g_status_minishell.status_pipe = 1;
			return (-1);
		}
		list = list->next;
	}
	return (0);
}
