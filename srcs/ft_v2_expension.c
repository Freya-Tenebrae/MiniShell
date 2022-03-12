/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_expension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:24:34 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/12 15:08:18 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_expension_inject(t_data **data, char *str, char **result)
{
	char	*tmp;
	int		i;
	char	*buff;

	i = 0;
	tmp = NULL;
	if (str[i] && str[i] == '?')
	{
		buff = ft_itoa(g_status_minishell.status_pipe);
		if (!buff)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		ft_str_writeon(result, buff);
		free(buff);
		if (!*result)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		return (1);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		ft_char_writeon(&tmp, str[i]);
		if (!tmp)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		i++;
	}
	if (ft_getenv(data, tmp) && ft_getenv(data, tmp)->value)
	{
		ft_str_writeon(result, ft_getenv(data, tmp)->value);
		if (!*result)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	if (tmp)
		free(tmp);
	if (i == 0)
	{
		ft_char_writeon(result, '$');
		if (!*result)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	return (i);
}

static void	ft_expension_with_quote(t_data **data, char **str)
{
	char	*result;
	char	quote;
	int		i;
	int		j;

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
				j = ft_expension_inject(data, &((*str)[i + 1]), &result);
				if (j != -1)
					i += j;
				else
					break ;
			}
			else
			{
				ft_char_writeon(&result, (*str)[i]);
				if (!result)
					return (ft_put_error_void(GENERIC_ERROR, "malloc error"));
			}
		}
		i++;
	}
	if (!result)
	{
		result = ft_strdup("");
		if (!result)
			return (ft_put_error_void(GENERIC_ERROR, "malloc error"));
	}
	free(*str);
	*str = result;
}

static int	ft_is_only_variable(t_data **data, char *str)
{
	size_t	i;
	int		j;
	int		k;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i + 1 < ft_strlen(str) && str[i + 1] == '?')
				return (0);
			j = ft_str_indexof(str + i + 1, '$');
			if (j == -1)
			{
				k = 0;
				while ((*data)->env[k])
				{
					if (ft_strcmp(str + i + 1, (*data)->env[k]->name) == 0)
					{
						// printf("A\n");
						return (!(*data)->env[k]->value);
					}
					k++;
				}
				// printf("B\n");
				return (str[0] == '$' && ft_strlen(str) > 1 && \
								ft_is_valid_variable_identifier(str + i + 1));
			}
			k = 0;
			while ((*data)->env[k])
			{
				if (!ft_is_nvalid_variable_identifier(str + i + 1, j))
				{
					// printf("C\n");
					return (0);
				}
				if (ft_strncmp(str + i + 1, (*data)->env[k]->name, j) == 0
				&& (j - i) >= ft_strlen((*data)->env[k]->name))
				{
					// printf("D\n");
					return (!(*data)->env[k]->value);
				}
				k++;
			}
		}
		i++;
	}
	// printf("E\n");
	return (0);
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
		(void) ft_is_only_variable;
		if (!ft_havequote(cursor->str) && ft_is_only_variable(data, cursor->str))
		{
			free(cursor->str);
			cursor->str = NULL;
		}
		ft_expension_with_quote(data, &(cursor->str));
		cursor = cursor->next;
	}
	// cursor = list;
	// while (cursor)
	// {
	// 	printf("'%s'\n", cursor->str);
	// 	cursor = cursor->next;
	// }
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
		{
			ft_char_writeon(&result, (*str)[i]);
			if (!result)
				return (ft_put_error_void(GENERIC_ERROR, "malloc error"));
		}
		i++;
	}
	if (!result)
	{
		result = ft_strdup("");
		if (!result)
			return (ft_put_error_void(GENERIC_ERROR, "malloc error"));
	}
	free(*str);
	*str = result;
}
