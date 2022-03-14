/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_expension.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:24:34 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/14 17:11:38 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_exp_inject3(char *tmp, int i, char **result)
{
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

static int	ft_exp_inject2(t_data **data, char *str, char **result)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
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
	return (ft_exp_inject3(tmp, i, result));
}

static int	ft_expension_inject(t_data **data, char *str, char **result)
{
	char	*buff;

	if (str[0] && str[0] == '?')
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
	return (ft_exp_inject2(data, str, result));
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

static int	test(t_data **data, char **str, int *i, char **result)
{
	int	j;

	j = ft_expension_inject(data, &((*str)[*i + 1]), result);
	if (j == -1)
		return (1);
	*i += j;
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
					if (test(data, str, &i, result))
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

static int	ft_is_only_variable3(t_data **data, char *str, size_t i, int j)
{
	int		k;

	k = 0;
	while ((*data)->env[k])
	{
		if (!ft_is_nvalid_variable_identifier(str + i + 1, j))
			return (0);
		if (ft_strncmp(str + i + 1, (*data)->env[k]->name, j) == 0
			&& (j - i) >= ft_strlen((*data)->env[k]->name))
			return (!(*data)->env[k]->value);
		k++;
	}
	return (-1);
}

static int	ft_is_only_variable2(t_data **data, char *str, size_t i)
{
	int		j;
	int		k;

	j = ft_str_indexof(str + i + 1, '$');
	if (j == -1)
	{
		k = 0;
		while ((*data)->env[k])
		{
			if (ft_strcmp(str + i + 1, (*data)->env[k]->name) == 0)
				return (!(*data)->env[k]->value);
			k++;
		}
		return (str[0] == '$' && ft_strlen(str) > 1 && \
						ft_is_valid_variable_identifier(str + i + 1));
	}
	return (ft_is_only_variable3(data, str, i, j));
}

static int	ft_is_only_variable(t_data **data, char *str)
{
	int		ret;
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (i + 1 < ft_strlen(str) && str[i + 1] == '?')
				return (0);
			ret = ft_is_only_variable2(data, str, i);
			if (ret != -1)
				return (ret);
		}
		i++;
	}
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

static void ft_expension_on_heredoc2(t_data **data, char **str, char **result)
{
	int		i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$')
		{
			i += ft_expension_inject(data, &((*str)[i + 1]), result);
		}
		else
		{
			ft_char_writeon(result, (*str)[i]);
			if (!*result)
				return (ft_put_error_void(GENERIC_ERROR, "malloc error"));
		}
		i++;
	}
}

void	ft_expension_on_heredoc(t_data **data, char **str)
{
	char	*result;

	result = 0;
	if (!str || !*str)
		return ;
	ft_expension_on_heredoc2(data, str, &result);
	if (!result)
	{
		result = ft_strdup("");
		if (!result)
			return (ft_put_error_void(GENERIC_ERROR, "malloc error"));
	}
	free(*str);
	*str = result;
}
