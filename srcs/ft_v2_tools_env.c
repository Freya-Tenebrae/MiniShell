/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_tools_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:57:18 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/15 13:35:41 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_is_whitespace_following(char *str)
{
	while (*str)
	{
		if (!ft_iswhitespace(*str))
			return (0);
		str++;
	}
	return (1);
}

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

void	ft_update_variable_value(t_env *variable, char *value)
{
	if (variable->value)
		free(variable->value);
	variable->value = value;
}

t_env	*ft_create_variable(char *name, char *value)
{
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (!res)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	res->name = ft_strdup(name);
	res->value = value;
	return (res);
}

t_env	*ft_clone_variable(t_env *env)
{
	char	*value;
	char	*name;
	t_env	*res;

	name = ft_strdup(env->name);
	if (!name)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	value = 0;
	if (env->value)
	{
		value = ft_strdup(env->value);
		if (!value)
			return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	}
	res = ft_create_variable(name, value);
	free(name);
	if (!res)
		return (0);
	return (res);
}

int	ft_env_tab_len(t_env **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
		i++;
	return (i);
}

t_env	**ft_clone_and_add_env(t_env **env, t_env *variable)
{
	t_env	**res;
	int		j;

	j = 0;
	if (!variable)
		return (0);
	res = malloc(sizeof(t_env) * (ft_env_tab_len(env) + 2));
	if (!res)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	while (env[j])
	{
		res[j] = ft_clone_variable(env[j]);
		if (!res[j])
		{
			ft_free_env(res);
			return (0);
		}
		j++;
	}
	res[j] = variable;
	res[j + 1] = 0;
	return (res);
}

static int	ft_try_replace(t_data **data, t_env *variable)
{
	t_env	*existing;

	existing = ft_getenv(data, variable->name);
	if (!existing || !variable->value)
		return (0);
	if (existing->value)
	{
		existing->value = 0;
		free(existing->value);
	}
	if (variable->value)
		existing->value = variable->value;
	return (1);
}

int	ft_is_nvalid_variable_identifier(char *str, int n)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) == 0)
		return (0);
	if (str[0] >= '0' && str[0] <= '9')
		return (0);
	while (str[i] && i < n)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_valid_variable_identifier(char *str)
{
	return (ft_is_nvalid_variable_identifier(str, (int) ft_strlen(str)));
}

int	ft_add_variable(t_data **data, t_env *variable)
{
	t_env	**copy;

	if (ft_try_replace(data, variable))
		return (0);
	copy = ft_clone_and_add_env((*data)->env, variable);
	if (!copy)
		return (-1);
	ft_free_envs(&((*data)->env), ft_get_size_env(&((*data)->env)));
	(*data)->env = copy;
	return (1);
}
