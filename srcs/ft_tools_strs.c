/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/03 18:25:51 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Clone le tableau spécifié. */

char	**ft_str_clonetab(char **strs)
{
	int		len;
	int		i;
	char	**res;

	len = 0;
	while (strs[len])
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (strs[i])
	{
		res[i] = ft_strdup(strs[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

/* Free le tableau spécifié */

void	ft_freestrs(char ***strs)
{
	char	**strs_ptr;

	strs_ptr = *strs;
	while (*strs_ptr != NULL)
	{
		free(*strs_ptr);
		*strs_ptr = NULL;
		strs_ptr++;
	}
	free(*strs);
	*strs = NULL;
}
