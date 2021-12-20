/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:18:37 by gadeneux          #+#    #+#             */
/*   Updated: 2021/12/20 02:20:41 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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

static int		ft_iswhitespace(char c)
{
	return (c == (char) 32 || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r');
}

static int		ft_readnext(char *str, int i, char **buffer)
{
	int q1 = 0;
	if (!str)
		return (-1);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	while (str[i])
	{
		if (str[i] == '"')
			q1++;
		if (!ft_iswhitespace(str[i]) || q1 % 2 != 0)
		{
			if (str[i] != '"' && !ft_writechar_on(buffer, str[i]))
				return (-1);
		} else {
			break ;
		}
		i++;
	}
	return (i);
}

static int		ft_str_is(char *str1, char *str2)
{
	if (!str1 && !str2)
		return (1);
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	int i = 0;
	int len = ft_strlen(str1);
	while (i < len && str1[i] == str2[i])
		i++;
	return (i == len);
}

static int		ft_gettype(char *str)
{
	if (!str)
		return (-1);
	if (ft_str_is(str, "<"))
		return (IN);
	if (ft_str_is(str, "<<"))
		return (DOUBLE_IN);
	if (ft_str_is(str, ">"))
		return (OUT);	
	if (ft_str_is(str, ">>"))
		return (DOUBLE_OUT);
	if (ft_str_is(str, "|"))
		return (PIPE);
	return (ARGUMENT);
}

int		ft_isoperator(char *str)
{
	if (!str)
		return (-1);
	return (ft_gettype(str) != -1);
}

static t_elem	*ft_createelem(char *str)
{
	if (!str)
		str = ft_strdup("");
	t_elem *res = malloc(sizeof(t_elem));
	if (!res)
		return (0);
	res->next = 0;
	res->str = ft_strdup(str);
	res->type = ft_gettype(str);
	return (res);
}

static t_elem	*ft_lastelem(t_elem *list)
{
	if (!list)
		return (0);
	t_elem *cursor = list;
	while (cursor->next != 0)
		cursor = cursor->next;
	return (cursor);
}

static int		ft_addon(t_elem **list, char *str)
{
	if (!list)
		return (-1);
	if (!(*list))
	{
		*list = ft_createelem(str);
		(*list)->type = ARGUMENT;
		if (!*list)
			return (-1);
		return (1);
	}
	t_elem *last = ft_lastelem(*list);
	if (!last)
		return (-1);
	last->next = ft_createelem(str);
	return (1);
}

t_elem	*ft_readcmd(char *str)
{
	int	i = 0;
	char *buffer = 0;
	t_elem *list = 0;
	if (!str)
		return (0);
	while ((i = ft_readnext(str, i, &buffer)) != -1 && (size_t) i < ft_strlen(str) && i != -1)
	{
		if (!ft_addon(&list, buffer))
			return (0);
		buffer = 0;
	}
	if (buffer)
	{
		if (!ft_addon(&list, buffer))
			return (0);
	}
	if (i == -1)
		return (0);
	if (buffer)
		free(buffer);
	return (list);
}
