/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strutils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/07 16:22:54 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

char	*ft_before(char *str, char c)
{
	char	*dst;
	int		l;
	int		i;

	if (!str)
		return (0);
	l = 0;
	while (str[l] && str[l] != c)
		++l;
	dst = malloc(l + 1);
	if (!dst)
		return (0);
	i = 0;
	while (str[i] && i < l)
	{
		dst[i] = str[i];
		++i;
	}
	dst[i] = 0;
	return (dst);
}

char	*ft_after(char *str, char c)
{
	int i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != c)
		i++;
	if (!str[i])
		return (ft_strdup(str));
	if (str[i] == c)
		i++;
	int len = ft_strlen(str) - i;
	char *res = malloc(len + 1);
	if (!res)
		return (0);
	int j = 0;
	while (str[i])
	{
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = 0;
	return (res);
}

char		*ft_chartostring(char c)
{
	char *str = malloc(sizeof(char) * 2);
	if (!str)
		return (0);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char		*ft_writechar_on(char **str, char c)
{
	if (!str)
		return (0);
	if (!(*str))
	{
		*str = ft_chartostring(c);
		return (*str);
	}
	char *res = malloc((sizeof(char) * ft_strlen(*str)) + 2);
	if (!res)
		return (0);
	int i = 0;
	while ((*str)[i] != '\0')
	{
		res[i] = (*str)[i];
		i++;
	}
	res[i] = c;
	res[i + 1] = '\0';
	free(*str);
	*str = res;
	return (res);
}

char		*ft_writestr_on(char **str, char *to_add)
{
	if (!str)
		return (0);
	if (!(*str))
	{
		*str = ft_strdup(to_add);
		return (*str);
	}
	char *res = ft_strjoin(*str, to_add);
	if (!res)
		return (0);
	free(*str);
	*str = res;
	return (res);
}

int		ft_iswhitespace(char c)
{
	return (c == (char) 32 || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

char *ft_str_substring(char *str, int begin, int end)
{
	char *res;

	res = 0;
	int i = begin;
	if (begin >= (int) ft_strlen(str))
		return (0);
	while (str[i] && i < end)
	{
		ft_writechar_on(&res, str[i]);
		i++;
	}
	return (res);
}

int	ft_str_indexof(char *str, char c)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_str_lastindexof(char *str, int from, char c)
{
	int i = from;
	int res = -1;
	if (from < 0 || from > (int) ft_strlen(str))
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			res = i;
		i++;
	}
	return (res);
}

int		ft_isquote(char c)
{
	return (c == '\'' || c == '"');
}