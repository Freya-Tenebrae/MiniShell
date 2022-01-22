/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 00:54:38 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/22 18:01:48 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

	// if (*infile && infile != NULL)
	// 	faire les pipes et modifie infile en consequence
	// else
	// 	skip list jusqu'au prochain pipe ou > / >> et ne modifie pas infile
t_elem	*ft_run_pipe(t_elem *list, char **infile)
{
	(void)infile;
	list = list->next;
	return (list);
}
