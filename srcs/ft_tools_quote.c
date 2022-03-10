/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:30:52 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/10 10:46:21 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Renvoie true si la chaine est valide, 0 s'il y a une erreur de quote. */

int	ft_check_quote(char *str)
{
	int		in_quote;
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	in_quote = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && (!quote || quote == str[i]))
		{
			quote = str[i];
			in_quote++;
		}
		if (in_quote % 2 == 0)
			quote = 0;
		i++;
	}
	if (in_quote && in_quote % 2 != 0)
		return (0);
	return (1);
}

/* Renvoie une nouvelle chaine de caractère qui prends uniquement */
/* le contenu de ce qu'il y a entre quote dans str. */

static char	*ft_return_empty_str(void)
{
	char	*res;

	res = ft_strdup("");
	if (!res)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	return (res);
}

static int	ft_keepinside_quote_init(char *str, int *strlen, char *q, int *i)
{
	if (!str)
		return (-1);
	*strlen = ft_strlen(str);
	*q = 0;
	*i = -1;
	return (0);
}

char	*ft_keepinside_quote(char *str)
{
	char	*res;
	char	q;
	int		i;
	int		strlen;

	if (ft_keepinside_quote_init(str, &strlen, &q, &i) == -1)
		return (NULL);
	res = NULL;
	if (ft_strcmp(str, "''") == 0 || ft_strcmp(str, "\"\"") == 0)
		return (ft_return_empty_str());
	while (++i < strlen)
	{
		if (ft_isquote(str[i]) && q == 0)
			q = str[i];
		else if (ft_isquote(str[i]) && q != 0 && str[i] == q)
			q = 0;
		else if (q == 0 || str[i] != q)
		{
			ft_char_writeon(&res, str[i]);
			if (!res || res == NULL)
				return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
		}
	}
	return (res);
}

int	ft_havequote(char *str)
{
	while (*str)
	{
		if (ft_isquote(*str))
			return (1);
		str++;
	}
	return (0);
}
