/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:18:37 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/05 17:28:22 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int		ft_readnext(char *str, int i, char **buffer)
{
	int in_quote = 0;
	char quote = 0;
	
	if (!str)
		return (READ_ERR);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	
	// Si débute par un opérateur, écris l'opérateur et renvoie.
	if (ft_char_isoperator(str[i]))
	{
		int j = 0;
		char c = str[i];
		while (ft_char_isoperator(str[i]))
		{
			if (j > 1 || str[i] != c)
				return (i);
			ft_writechar_on(buffer, str[i]);
			i++;
			j++;
		}
		return (i);
	}
	
	while (str[i])
	{
		// Si le char est une quote, et que c'est l'ouverture ou une fermeture de quote
		// Si fermeture, vérifie qu'il s'agit de la bonne quote.
		if (ft_isquote(str[i]) && (!quote || quote == str[i]))
		{
			quote = str[i];
			in_quote++;
		}
		
		// si il s'agit pas d'un whitespace, ou si c'est entre quote
		// écrire.
		if (!ft_iswhitespace(str[i]) || in_quote % 2 != 0)
		{
			if (/*(!quote || str[i] != quote) &&*/ !ft_writechar_on(buffer, str[i]))
				return (READ_ALLOC_ERR);
		} else {
			break ;
		}

		// En dehors des parenthèses, si précédé par un opérateur, break.
		if (in_quote % 2 == 0 && ft_char_isoperator(str[i + 1]))
		{
			i++;
			break ;
		}
		
		// réinitialise la quote à null en cas de fermeture.
		if (in_quote % 2 == 0)
			quote = 0;
			
		i++;
	}
	if (in_quote && in_quote % 2 != 0)
		return (READ_QUOTE_ERR);
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
	if (ft_str_is(str, "||"))
		return (DOUBLE_PIPE);
	if (ft_str_is(str, "&"))
		return (AND);
	if (ft_str_is(str, "&&"))
		return (DOUBLE_AND);
	return (ARGUMENT);
}

int		ft_char_isoperator(char c)
{
	if (c == '<')
		return (IN);
	if (c == '>')
		return (OUT);
	if (c == '|')
		return (PIPE);
	if (c == '&')
		return (AND);
	return (0);
}

int		ft_str_isoperator(char *str)
{
	if (!str)
		return (-1);
	return (ft_gettype(str) != -1);
}

static t_elem	*ft_createelem(char *str, int type)
{
	if (!str)
		str = ft_strdup("");

	t_elem *res = malloc(sizeof(t_elem));
	if (!res)
		return (0);
	res->next = 0;
	res->str = str;
	res->type = type;
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

static int		ft_addon(t_elem **list, char *str, int type)
{
	if (!list)
		return (-1);
	if (!(*list))
	{
		*list = ft_createelem(str, type);
		(*list)->type = ARGUMENT;
		if (!*list)
			return (-1);
		return (1);
	}
	t_elem *last = ft_lastelem(*list);
	if (!last)
		return (-1);
	last->next = ft_createelem(str, type);
	return (1);
}

char	*ft_keepinside_q(char *str)
{
	char *res;

	res = 0;
	if (!str)
		return (0);
	char q = 0;
	for (size_t i = 0; i < ft_strlen(str); ++i)
	{
		if (ft_isquote(str[i]) && q == 0)
		{
			q = str[i];
		} else
		if (ft_isquote(str[i]) && q != 0 && str[i] == q)
		{
			q = 0;
		} else
		if (q == 0 || str[i] != q)
			ft_writechar_on(&res, str[i]);
	}
	return (res);
}

t_elem	*ft_readcmd(char *str, int *ret)
{
	int	i = 0;
	char *buffer = 0;
	t_elem *list = 0;
	if (!str)
		return (0);
	while ((i = ft_readnext(str, i, &buffer)) != -1 && (size_t) i < ft_strlen(str) && i >= 0)
	{
		// printf("%-3d [%s]\n", i, buffer);
		if (!ft_addon(&list, ft_keepinside_q(buffer), ft_gettype(buffer)))
			return (0);
		buffer = 0;
	}
	if (i != -1)
	{
		// printf("%-3d [%s]\n", i, buffer);
		if (!ft_addon(&list, ft_keepinside_q(buffer), ft_gettype(buffer)))
			return (0);
	}
	if (i < 0)
	{
		*ret = i;
		return (0);
	}
	*ret = READ_OK;
	if (buffer)
		free(buffer);
	return (list);
}
