/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_access.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 16:12:00 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/21 16:43:19 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_check_access_ok_in_loop_is_dir(t_elem **list)
{
	struct stat	*statbuf;

	statbuf = malloc(sizeof(struct stat));
	if (!statbuf || statbuf == NULL)
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	stat((*list)->str, statbuf);
	if ((statbuf->st_mode & S_IFMT) == S_IFDIR)
	{
		free(statbuf);
		return (ft_put_error(IS_DIRECTORY_ERROR, (*list)->str));
	}
	else
	{
		free(statbuf);
		return (0);
	}
}

static int	ft_fcheck_access_ok_out_loop_in(t_elem **list)
{
	*list = (*list)->next;
	if (!*list || *list == NULL || (*list)->type != ARGUMENT)
		return (ft_put_error(GENERIC_ERROR, "ambiguous redirect"));
	if (access((*list)->str, F_OK) != 0)
		return (ft_put_error(FILE_ERROR, (*list)->str));
	else if (access((*list)->str, R_OK) != 0)
		return (-1);
	else if (ft_check_access_ok_in_loop_is_dir(list) != 0)
		return (-1);
	return (0);
}

static int	ft_check_access_ok_out_loop(t_elem **list)
{
	if ((*list)->type == IN)
	{
		if (ft_fcheck_access_ok_out_loop_in(list) == -1)
			return (-1);
	}
	if ((*list)->type == OUT || (*list)->type == DOUBLE_OUT)
	{
		*list = (*list)->next;
		if (!*list || *list == NULL || (*list)->type != ARGUMENT)
			return (ft_put_error(GENERIC_ERROR, "ambiguous redirect"));
		if (access((*list)->str, F_OK) == 0)
		{
			if (access((*list)->str, W_OK) != 0)
				return (-1);
			else if (ft_check_access_ok_in_loop_is_dir(list) != 0)
				return (-1);
		}
	}
	return (0);
}

int	ft_check_access_out_ok(t_elem *list)
{
	if (list != NULL && list->type == PIPE)
		list = list->next;
	while (list != NULL && list->type != PIPE)
	{
		if (ft_check_access_ok_out_loop(&list) == -1)
		{
			g_status_minishell.status_pipe = 1;
			return (-1);
		}
		list = list->next;
	}
	return (0);
}
