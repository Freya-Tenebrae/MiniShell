/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:18:37 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/23 02:02:06 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Écrit sur buffer le contenu du prochain élément à partir de l'index i */
/* jusqu'au prochain opérateur. */

static int	ft_readnext(char *str, int i, char **buffer)
{
	int		in_quote;
	char	quote;
	int		j;
	char	c;

	if (!str)
		return (READ_ERR);
	in_quote = 0;
	quote = 0;
	while (str[i] && ft_str_iswhitespace(str[i]))
		i++;
	if (ft_char_isoperator(str[i]))
	{
		j = 0;
		c = str[i];
		while (ft_char_isoperator(str[i]))
		{
			if (j > 1 || str[i] != c)
				return (i);
			ft_char_writeon(buffer, str[i]);
			i++;
			j++;
		}
		return (i);
	}
	while (str[i])
	{
		if (ft_isquote(str[i]) && (!quote || quote == str[i]))
		{
			quote = str[i];
			in_quote++;
		}
		if (!ft_str_iswhitespace(str[i]) || in_quote % 2 != 0)
		{
			if (/*(!quote || str[i] != quote) &&*/ !ft_char_writeon(buffer, str[i]))
				return (READ_ALLOC_ERR);
		}
		else
			break ;
		if (in_quote % 2 == 0 && ft_char_isoperator(str[i + 1]))
		{
			i++;
			break ;
		}
		if (in_quote % 2 == 0)
			quote = 0;
		i++;
	}
	return (i);
}

/* Créer une liste de t_elem à partir de la commande str */
/* et stocke le retour dans ret */

t_elem	*ft_read_command(char *str, int *ret)
{
	int		i;
	int		strlen;
	char	*buffer;
	t_elem	*list;

	if (!str || str == NULL)
		return (NULL);
	i = 0;
	buffer = NULL;
	list = NULL;
	strlen = ft_strlen(str);
	while ((i = ft_readnext(str, i, &buffer)) != -1 && i < strlen && i >= 0)
	{
		// check if list is null / !list;
		if (!ft_tools_elem_add(&list, ft_keepinside_quote(buffer)))
		{
			if (buffer)
				free(buffer);
			return (NULL);
		}
		if (buffer)
			free(buffer);
		buffer = 0;
	}
	if (i != -1)
	{
		// check if list is null / !list;
		if (!ft_tools_elem_add(&list, ft_keepinside_quote(buffer)))
		{
			if (buffer)
				free(buffer);
			return (NULL);
		}
	}
	if (i < 0)
	{
		*ret = i;
		if (buffer)
			free(buffer);
		return (NULL);
	}
	*ret = READ_OK;
	if (buffer)
		free(buffer);
	return (list);
}
