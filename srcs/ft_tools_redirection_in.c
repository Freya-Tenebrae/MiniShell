/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_redirection_in.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:32:17 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/22 18:26:39 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

	// check if file exist and if it's readable (chmod read ok) 
		// with "acess(path, R_OK);"
	// if not put an erro and return
	// open file and check error
	// read all file and put in in a char *
	// close file
	// return all read file in char*
	// return NULL if error
char	*ft_tools_get_in(char *path)
{
	(void)path;
	return (NULL);
}

	// read on standard entry until "word" is found and put in in a char *
	// close file
	// return all read in char*
	// return NULL if error
char	*ft_tools_get_double_in(char *word)
{
	(void)word;
	return (NULL);
}
