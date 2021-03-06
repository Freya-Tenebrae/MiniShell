/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:38:48 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/21 13:58:15 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Renvoie un int qui représente l'opérateur en question */

static int	ft_put_operator_error(char *str)
{
	char	c;
	char	*cstr;

	if (str[1] != str[0])
		c = str[1];
	else if (ft_strlen(str) > 2)
		c = str[2];
	else
		return (ft_put_error(GENERIC_ERROR, "Erreur de syntaxe"));
	cstr = ft_char_tostring(c);
	if (cstr)
	{
		ft_put_error(OPERATOR_ERROR, cstr);
		free(cstr);
		return (-1);
	}
	else
		return (ft_put_error(GENERIC_ERROR, "Erreur de syntaxe"));
}

int	ft_get_operator_type(char *str)
{
	if (!str)
		return (-1);
	if (ft_strlen(str) != 0 && ft_char_isoperator(str[0]))
	{
		if (ft_strcmp(str, "<") == 0)
			return (IN);
		else if (ft_strcmp(str, "<<") == 0)
			return (DOUBLE_IN);
		else if (ft_strcmp(str, ">") == 0)
			return (OUT);
		else if (ft_strcmp(str, ">>") == 0)
			return (DOUBLE_OUT);
		else if (ft_strcmp(str, "|") == 0)
			return (PIPE);
		else
			return (ft_put_operator_error(str));
	}
	return (ARGUMENT);
}

/* Renvoie true si le str spécifié est un opérateur */

int	ft_char_isoperator(char c)
{
	if (c == '<')
		return (IN);
	if (c == '>')
		return (OUT);
	if (c == '|')
		return (PIPE);
	return (0);
}
