/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_tools_env3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:57:18 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 18:27:25 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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
