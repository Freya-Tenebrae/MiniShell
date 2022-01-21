/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_redirection_out.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:32:17 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/21 03:55:09 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

t_elem	*ft_tools_push_out(t_elem *list, char **infile)
{
	list = list->next;
	(void)infile;
	// check if file exist and if it's writable (chmod write ok) with "acess(path, W_OK);"
	// if it didn't exist created it
	// if it didn't have the right to do it, just put an error
	// open file and check error
	// erased everything and write on it
	// close file
	return (list);
}

t_elem	*ft_tools_push_double_out(t_elem *list, char **infile)
{
	list = list->next;
	(void)infile;
	// check if file exist and if it's writable (chmod write ok) with "acess(path, W_OK);"
	// if it didn't exist created it
	// if it didn't have the right to do it, just put an error
	// open file and check error
	// write on it after last line
	// close file
	return (list);
}

