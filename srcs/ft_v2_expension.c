/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_expension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:24:34 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 11:41:46 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_expension_with_quote4(t_data **data, char **str, int *i,
		char **result)
{
	int	j;

	j = ft_expension_inject(data, &((*str)[*i + 1]), result);
	if (j == -1)
		return (1);
	*i += j;
	return (0);
}

static int	ft_expension_with_quote3(char **result, char **str, int i)
{
	ft_char_writeon(result, (*str)[i]);
	if (!*result)
	{
		ft_put_error_void(GENERIC_ERROR, "malloc error");
		return (-1);
	}
	return (0);
}

static void	ft_expension_with_quote2(t_data **data, char **str, char **result)
{
	char	quote;
	int		i;

	i = -1;
	quote = 0;
	while ((*str)[++i])
	{
		if ((*str)[i] != '$' || !ft_isquote((*str)[i + 1]) || quote)
		{
			if (quote || !ft_isquote((*str)[i]))
			{
				if (quote && (*str)[i] == quote)
					quote = 0;
				else if ((*str)[i] == '$' && (!quote || quote != '\''))
				{
					if (ft_expension_with_quote4(data, str, &i, result))
						break ;
				}
				else if (ft_expension_with_quote3(result, str, i) == -1)
					return ;
			}
			else
				quote = (*str)[i];
		}
	}
}

static void	ft_expension_with_quote(t_data **data, char **str)
{
	char	*result;

	result = 0;
	if (!str || !*str)
		return ;
	ft_expension_with_quote2(data, str, &result);
	if (!result)
	{
		result = ft_strdup("");
		if (!result)
			return (ft_put_error_void(GENERIC_ERROR, "malloc error"));
	}
	free(*str);
	*str = result;
}

void	ft_expension_on_command(t_data **data, t_elem *list)
{
	t_elem	*cursor;

	cursor = list;
	while (cursor)
	{
		if (cursor->type == DOUBLE_IN)
		{
			cursor = cursor->next->next;
			continue ;
		}
		if (!ft_havequote(cursor->str)
			&& ft_is_only_variable(data, cursor->str))
		{
			free(cursor->str);
			cursor->str = NULL;
		}
		ft_expension_with_quote(data, &(cursor->str));
		cursor = cursor->next;
	}
}
