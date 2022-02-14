/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_str_replace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/14 03:08:59 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Écris un caractère sur la chaine str (Free l'ancien str et remplace). */
/* Si la chaine str n'existe pas elle sera allouée. */

char	*ft_char_writeon(char **str, char c)
{
	char	*res;
	int		i;

	if (!str)
		return (NULL);
	if (!(*str) || *str == NULL)
	{
		*str = ft_char_tostring(c);
		if (!*str || *str == NULL)
			return (NULL);
		return (*str);
	}
	res = malloc((sizeof(char) * ft_strlen(*str)) + 2);
	if (!res || res == NULL)
		return (NULL);
	i = 0;
	while ((*str)[i] != '\0')
	{
		res[i] = (*str)[i];
		i++;
	}
	free(*str);
	res[i] = c;
	res[i + 1] = '\0';
	*str = res;
	res = NULL;
	return (*str);
}

/* Écris une string sur la chaine str (Free l'ancien str et remplace). */
/* Si la chaine str n'existe pas elle sera allouée. */

char	*ft_str_writeon(char **str, char *to_add)
{
	char	*res;

	if (!str)
		return (NULL);
	if (!(*str) || *str == NULL)
	{
		*str = ft_strdup(to_add);
		if (!*str || *str == NULL)
			return (NULL);
		return (*str);
	}
	res = ft_strjoin(*str, to_add);
	if (!res || res == NULL)
		return (NULL);
	free(*str);
	*str = res;
	return (res);
}
