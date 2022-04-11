/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_tools_env2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:57:18 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/21 16:09:20 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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
