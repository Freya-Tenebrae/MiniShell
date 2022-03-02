/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:30:52 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/02 16:45:48 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Renvoie true si le char spécifié est une quote. */

int	ft_isquote(char c)
{
	return (c == '\'' || c == '"');
}

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
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (NULL);
	}
	return (res);
}

char	*ft_keepinside_quote(char *str)
{
	char	*res;
	char	q;
	int		i;
	int		strlen;

	if (!str)
	{
		return (NULL);
	}
	if (ft_strcmp(str, "''") == 0 || ft_strcmp(str, "\"\"") == 0)
		return (ft_return_empty_str());
	res = NULL;
	q = 0;
	i = -1;
	strlen = ft_strlen(str);
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
				ft_put_error(GENERIC_ERROR, "malloc error");
		}

	}
	return (res);
}

int		ft_havequote(char *str)
{
	while (*str)
	{
		if (ft_isquote(*str))
			return (1);
		str++;
	}
	return (0);
}