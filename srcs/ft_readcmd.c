/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:18:37 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/22 17:31:41 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int		ft_addon(t_elem **list, char *str, int type);

/* Écrit sur buffer le contenu du prochain élément à partir de l'index i */ 
/* jusqu'au prochain opérateur. */

static int		ft_readnext(char *str, int i, char **buffer)
{
	int in_quote = 0;
	char quote = 0;
	
	if (!str)
		return (READ_ERR);
	while (str[i] && ft_str_iswhitespace(str[i]))
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
			ft_char_writeon(buffer, str[i]);
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
		if (!ft_str_iswhitespace(str[i]) || in_quote % 2 != 0)
		{
			if (/*(!quote || str[i] != quote) &&*/ !ft_char_writeon(buffer, str[i]))
			{
				return (READ_ALLOC_ERR);
			}
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
	return (i);
}

/* Créer une liste de t_elem à partir de la commande str */
/* et stocke le retour dans ret */

t_elem	*ft_read_command(char *str, int *ret)
{
	int	i = 0;
	char *buffer = 0;
	t_elem *list = 0;
	if (!str)
		return (0);
	while ((i = ft_readnext(str, i, &buffer)) != -1 && (size_t) i < ft_strlen(str) && i >= 0)
	{
		// printf("%-3d [%s]\n", i, buffer);
		if (!ft_addon(&list, ft_keepinside_quote(buffer), ft_get_operator_type(buffer)))
		{
			if (buffer)
				free(buffer);
			return (0);
		}
		if (buffer)
			free(buffer);
		buffer = 0;
	}
	if (i != -1)
	{
		// printf("%-3d [%s]\n", i, buffer);
		if (!ft_addon(&list, ft_keepinside_quote(buffer), ft_get_operator_type(buffer)))
		{
			if (buffer)
				free(buffer);
			return (0);
		}
	}
	if (i < 0)
	{
		*ret = i;
		if (buffer)
			free(buffer);
		return (0);
	}
	*ret = READ_OK;
	if (buffer)
		free(buffer);
	return (list);
}

/* Créer un élément */

static t_elem	*ft_createelem(char *str, int type)
{
	t_elem		*res;

	if (!str)
		str = ft_strdup("");

	res = malloc(sizeof(t_elem));
	if (!res)
		return (0);
	res->next = 0;
	res->str = str;
	res->type = type;
	return (res);
}

/* Renvoie le dernier élément de la liste */

static t_elem	*ft_lastelem(t_elem *list)
{
	t_elem		*cursor;

	if (!list)
		return (0);
	cursor = list;
	while (cursor->next != 0)
		cursor = cursor->next;
	return (cursor);
}

/* Ajoute un élément à la liste, prends un double pointeur pour créer la liste */
/* si elle n'éxiste pas */

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
