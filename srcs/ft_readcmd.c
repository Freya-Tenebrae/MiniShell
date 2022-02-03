/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:18:37 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/03 15:00:45 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Écrit sur buffer le contenu du prochain élément à partir de l'index i */
/* jusqu'au prochain opérateur. */

static int	ft_read_next_if_operator(char *str, int i, char **buffer)
{
	while (ft_char_isoperator(str[i]))
	{
		if (ft_char_writeon(buffer, str[i]) == NULL)
			return (-1);
		i++;
	}
	return (i);
}

static int	ft_read_next_if_argument_or_command(char *str, int i, char **buffer)
{
	int		in_quote;
	char	quote;

	in_quote = 0;
	quote = 0;
	while (str[i])
	{
		if (ft_isquote(str[i]) && (!quote || quote == str[i]))
		{
			quote = str[i];
			in_quote++;
		}
		if (!ft_str_iswhitespace(str[i]) || in_quote % 2 != 0)
		{
			if (!ft_char_writeon(buffer, str[i]))
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

static int	ft_read_next(char *str, int i, char **buffer)
{
	if (!str)
		return (READ_ERR);
	while (str[i] && ft_str_iswhitespace(str[i]))
		i++;
	if (ft_char_isoperator(str[i]))
		return (ft_read_next_if_operator(str, i, buffer));
	return (ft_read_next_if_argument_or_command(str, i, buffer));
}

/* Créer une liste de t_elem à partir de la commande str */
/* et stocke le retour dans ret */

t_elem	*ft_read_command(char *str, int *ret)
{
	int		i;
	int		strlen;
	char	*buffer;
	char	*buffer_new;
	t_elem	*list;

	if (!str || str == NULL)
		return (NULL);
	i = 0;
	buffer = NULL;
	list = NULL;
	strlen = ft_strlen(str);
	i = ft_read_next(str, i, &buffer);
	buffer_new = ft_keepinside_quote(buffer);
	free(buffer);
	buffer = buffer_new;
	while (i != -1 && i < strlen && i >= 0)
	{
		if (buffer == NULL)
		{
			ft_tools_free_elem(&list);
			return (NULL);
		}
		if (ft_tools_elem_add(&list, buffer) == -1)
		{
			free(buffer);
			ft_tools_free_elem(&list);
			return (NULL);
		}
		buffer = NULL;
		i = ft_read_next(str, i, &buffer);
		buffer_new = ft_keepinside_quote(buffer);
		free(buffer);
		buffer = buffer_new;
	}
	if (i != -1)
	{
		if (buffer == NULL)
		{
			ft_tools_free_elem(&list);
			return (NULL);
		}
		if (ft_tools_elem_add(&list, buffer) == -1)
		{
			if (buffer && buffer != NULL)
				free(buffer);
			ft_tools_free_elem(&list);
			return (NULL);
		}
	}
	if (i < 0)
	{
		*ret = i;
		if (buffer && buffer != NULL)
			free(buffer);
		ft_tools_free_elem(&list);
		return (NULL);
	}
	*ret = READ_OK;
	return (list);
}
