/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:18:37 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/05 20:42:39 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Écrit sur buffer le contenu du prochain élément à partir de l'index i */
/* jusqu'au prochain opérateur. */

static void	ft_check_if_start_or_end_quote(char *str, int i, \
													char *quote, int *in_quote)
{
	if (ft_isquote(str[i]) && (!*quote || *quote == str[i]))
	{
		*quote = str[i];
		*in_quote += 1;
	}
}

static int	ft_read_next_if_argument_or_command(char *str, int i, char **buffer)
{
	int		in_quote;
	char	quote;

	in_quote = 0;
	quote = 0;
	while (str[i])
	{
		ft_check_if_start_or_end_quote(str, i, &quote, &in_quote);
		if (!ft_iswhitespace(str[i]) || in_quote % 2 != 0)
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

int	ft_read_cmd(char *str, int i, char **buffer, int *is_operator)
{
	char	*new_buffer;

	if (!str)
		return (READ_ERR);
	while (str[i] && ft_iswhitespace(str[i]))
		i++;
	if (ft_char_isoperator(str[i]))
	{
		*is_operator = 0;
		i = ft_read_next_if_operator(str, i, buffer);
		return (i);
	}
	*is_operator = 1;
	i = ft_read_next_if_argument_or_command(str, i, buffer);
	new_buffer = ft_keepinside_quote(*buffer);
	free(*buffer);
	*buffer = new_buffer;
	return (i);
}
