/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:30:52 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/04 14:37:59 by cmaginot         ###   ########.fr       */
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

char	*ft_keepinside_quote(char *str)
{
	char	*res;
	char	q;
	int		i;
	int		strlen;

	if (!str)
		return (NULL);
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
			ft_char_writeon(&res, str[i]);
	}
	return (res);
}
