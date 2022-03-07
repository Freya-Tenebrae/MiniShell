/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_expension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:24:34 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/07 14:35:59 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_expension_inject(t_data **data, char *str, char **result)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		ft_char_writeon(&tmp, str[i]);
		i++;
	}
	if (ft_getenv(data, tmp) && ft_getenv(data, tmp)->value)
	{
		ft_str_writeon(result, ft_getenv(data, tmp)->value);
	}
	if (tmp)
		free(tmp);
	if (i == 0)
		ft_char_writeon(result, '$');
	return (i);
}

static void	ft_expension_with_quote(t_data **data, char **str)
{
	char	*result;
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	result = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && ft_isquote((*str)[i + 1]) && !quote)
		{
			i++;
			continue ;
		}
		if (!quote && ft_isquote((*str)[i]))
			quote = (*str)[i];
		else
		{
			if (quote && (*str)[i] == quote)
				quote = 0;
			else if ((*str)[i] == '$' && (!quote || quote != '\''))
			{
				i += ft_expension_inject(data, &((*str)[i + 1]), &result);
			}
			else
				ft_char_writeon(&result, (*str)[i]);
		}
		i++;
	}
	if (!result)
		result = ft_strdup("");
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
		if (!ft_havequote(cursor->str) && cursor->str[0] == '$' && ft_is_valid_variable_identifier(cursor->str + 1)
		&& !ft_getenv(data, cursor->str + 1))
		{
			free(cursor->str);
			cursor->str = NULL;
		}
		ft_expension_with_quote(data, &(cursor->str));
		cursor = cursor->next;
	}
}

void	ft_expension_on_heredoc(t_data **data, char **str)
{
	char	*result;
	int		i;

	i = 0;
	result = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			i += ft_expension_inject(data, &((*str)[i + 1]), &result);
		}
		else
			ft_char_writeon(&result, (*str)[i]);
		i++;
	}
	if (!result)
		result = ft_strdup("");
	free(*str);
	*str = result;
}
