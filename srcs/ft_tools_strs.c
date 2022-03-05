/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_strs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/05 14:56:14 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Clone le tableau spécifié. */

char	**ft_str_clonetab(char **strs)
{
	char	**res;
	int		len;
	int		i;

	len = 0;
	while (strs[len])
		len++;
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (NULL);
	}
	i = 0;
	while (strs[i])
	{
		res[i] = ft_strdup(strs[i]);
		if (res[i] == NULL)
		{
			ft_put_error(GENERIC_ERROR, "malloc error");
			ft_freestrs(&res);
			return (NULL);
		}
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
