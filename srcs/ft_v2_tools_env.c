/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_tools_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:57:18 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 18:25:24 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	test(char **value, char **res, int i)
{
	if (ft_is_whitespace_following(*value + i))
		return (0);
	if (!(*value)[i + 1] || !ft_iswhitespace((*value)[i]) || \
											!ft_iswhitespace((*value)[i + 1]))
	{
		ft_char_writeon(res, (*value)[i]);
		if (!*res || *res == NULL)
		{
			free(value);
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		}
	}
	return (1);
}

static int	ft_trim_variable_value(char **value)
{
	char	*res;
	int		ret;
	int		i;

	i = 0;
	res = 0;
	if (!value || !*value)
		return (0);
	i = 0;
	while ((*value)[i] && ft_iswhitespace((*value)[i]))
		i++;
	while ((*value)[i])
	{
		ret = test(value, &res, i);
		if (ret == 0)
			break ;
		if (ret == -1)
			return (-1);
		i++;
	}
	free(*value);
	*value = res;
	return (1);
}

int	ft_create_or_update_variable(t_data **data, char *variable_name, \
																	char *value)
{
	t_env	*variable;
	int		ret;

	ret = 0;
	if (ft_trim_variable_value(&value) == -1)
		return (-1);
	variable = ft_getenv(data, variable_name);
	if (!variable)
	{
		variable = ft_create_variable(variable_name, value);
		if (!variable)
			return (-1);
		ret = ft_add_variable(data, variable);
		if (!ret)
			free(variable);
		if (ret == -1)
			return (-1);
	}
	else
		ft_update_variable_value(variable, value);
	return (1);
}

void	ft_free_variable(t_env *env)
{
	if (!env)
		return ;
	free(env->name);
	if (env->value)
		free(env->value);
	free(env);
}
