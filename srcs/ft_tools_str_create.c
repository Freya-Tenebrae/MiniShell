/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_str_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/14 05:23:50 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Récupère tout ce qui se trouve avant le premier caractère c dans */
/* la chaine str. */

char	*ft_str_before(char *str, char c)
{
	char	*res;
	int		l;
	int		i;

	if (!str)
		return (NULL);
	l = 0;
	while (str[l] && str[l] != c)
		++l;
	res = malloc(l + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && i < l)
	{
		res[i] = str[i];
		++i;
	}
	res[i] = 0;
	return (res);
}

/* Récupère tout ce qui se trouve après le premier caractère c dans */
/* la chaine str. */

char	*ft_str_after(char *str, char c)
{
	int		i;
	int		j;
	int		strlen;
	char	*res;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (ft_strdup(str));
	if (str[i] == c)
		i++;
	strlen = ft_strlen(str) - i;
	res = malloc(strlen + 1);
	if (!res)
		return (NULL);
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	return (res);
}

/* Concerti un caractère en chaine de caractère */

char	*ft_char_tostring(char c)
{
	char	*str;

	str = malloc(sizeof(char) * 2);
	if (!str)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (NULL);
	}
	str[0] = c;
	str[1] = '\0';
	return (str);
}
