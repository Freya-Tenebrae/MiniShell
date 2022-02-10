/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_str_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/10 18:15:42 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Récupère tout ce qui se trouve avant le premier caractère c dans */
/* la chaine str. */

char	*ft_str_before(char *str, char c)
{
	char	*dst;
	int		l;
	int		i;

	if (!str)
		return (NULL);
	l = 0;
	while (str[l] && str[l] != c)
		++l;
	dst = malloc(l + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (str[i] && i < l)
	{
		dst[i] = str[i];
		++i;
	}
	dst[i] = 0;
	return (dst);
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
		return (NULL);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

/* Alloue une chaine de caractère qui se trouve entre begin et */
/* end, dans la chaine str. */

char	*ft_str_substring(char *str, int begin, int end)
{
	char	*res;
	int		i;

	res = 0;
	i = begin;
	if (!str)
		return (NULL);
	if (begin >= (int) ft_strlen(str) || end >= (int) ft_strlen(str) || \
		begin < 0 || end < 0)
		return (NULL);
	if (begin > end)
		return (NULL);
	while (str[i] && i < end)
	{
		ft_char_writeon(&res, str[i]);
		i++;
	}
	return (res);
	// fonction to delete if stayed unused
}
