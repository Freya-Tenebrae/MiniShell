/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_expension_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 11:47:18 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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

int	ft_is_only_variable(t_data **data, char *str)
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

static void	ft_expension_on_heredoc2(t_data **data, char **str, char **result)
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
