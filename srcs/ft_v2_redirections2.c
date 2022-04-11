/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_redirections2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:45:06 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/21 12:43:20 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_redirection_open_all(t_data **data, t_elem *list)
{
	if (ft_redirection_open_in(data, list) == 0)
		return (0);
	ft_redirection_open_out(list);
	return (1);
}

char	*ft_get_filename_in(t_elem *list)
{
	char	*result;

	result = NULL;
	while (list)
	{
		if (list->type == PIPE)
			break ;
		if (list->type == IN)
			result = list->next->str;
		list = list->next;
	}
	return (result);
}

char	*ft_redirection_get_in(t_elem *cmd)
{
	char	*result;

	result = NULL;
	while (cmd)
	{
		if (cmd->type == PIPE)
			break ;
		if (cmd->in_content && cmd->in_content != NULL)
			result = cmd->in_content;
		cmd = cmd->next;
	}
	return (result);
}

char	*ft_redirection_get_heredoc(t_elem *cmd)
{
	char	*result;

	result = NULL;
	while (cmd)
	{
		if (cmd->type == PIPE)
			break ;
		if (cmd->type == DOUBLE_IN)
			result = cmd->next->str;
		cmd = cmd->next;
	}
	return (result);
}
