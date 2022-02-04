/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_str_get_index.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/04 14:38:00 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Renvoie l'index de la première occurence du caractère c */
/* dans la chaine str, ou -1 si aucun résultat. */

int	ft_str_indexof(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/* Renvoie l'index de la dernière occurence du caractère c */
/* dans la chaine str, ou -1 si aucun résultat. */

int	ft_str_lastindexof(char *str, int from, char c)
{
	int	i;
	int	res;

	i = from;
	res = -1;
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
