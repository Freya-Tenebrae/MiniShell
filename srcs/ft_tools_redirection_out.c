/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_redirection_out.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:32:17 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/20 17:26:07 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

t_elem	*ft_tools_push_out(t_elem *list, char **infile)
{
	list = list->next;
	(void)infile;
	return (list);
	// TODO
}

t_elem	*ft_tools_push_double_out(t_elem *list, char **infile)
{
	list = list->next;
	(void)infile;
	return (list);
	// TODO
}

