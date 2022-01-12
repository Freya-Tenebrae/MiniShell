/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:38:48 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/12 17:11:59 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Renvoie un int qui représente l'opérateur en question */

int		ft_get_operator_type(char *str)
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

/* Renvoie true si le str spécifié est un opérateur */

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

/* Renvoie true si le str spécifié est un opérateur */

int		ft_str_isoperator(char *str)
{
	if (!str)
		return (-1);
	return (ft_get_operator_type(str) != -1);
}
