/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:52 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/09 17:50:54 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	ft_putenv(t_env **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i]->name);
		ft_putstr("\n");
		i++;
	}
}

int	ft_str_equal(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if ((s1 == 0 && s2 == 0) || (s1 == NULL && s2 == NULL))
		return (1);
	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (i == ft_strlen(s1));
}

t_env	**ft_clone_without_env(t_data **data, char *identifier)
{
	t_env	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	res = malloc(sizeof(t_env) * (ft_env_tab_len((*data)->env)));
	if (!res)
		return (NULL);
	while ((*data)->env[i])
	{
		if (!ft_str_equal((*data)->env[i]->name, identifier))
		{
			res[j] = ft_clone_variable((*data)->env[i]);
			if (!res[j])
			{
				ft_free_envs(&((*data)->env), ft_get_size_env(&((*data)->env)));
				return (NULL);
			}
			j++;
		}
		i++;
	}
	res[j] = 0;
	return (res);
}

int	ft_unset_env(t_data **data, char *identifier)
{
	t_env	**copy;

	if (!identifier)
		return (-1);
	if (!ft_getenv(data, identifier))
		return (0);
	copy = ft_clone_without_env(data, identifier);
	if (!copy)
	{
		ft_put_error(GENERIC_ERROR, "malloc error")
		return (-2);
	}
	ft_free_envs(&((*data)->env), ft_get_size_env(&((*data)->env)));
	(*data)->env = copy;
	return (0);
}

int		ft_run_bi_unset(t_data **data, char **cmd_args)
{
	int	i;
	int	res;

	i = 1;
	if (!cmd_args || !cmd_args[1])
		return (2);
	while (cmd_args[i])
	{
		if (!ft_is_valid_variable_identifier(cmd_args[i]))
		{
			ft_put_error(UNSET_ERROR, cmd_args[i]);
			return (1);
		}
		else
		{
			res = ft_unset_env(data, cmd_args[i]);
			if (res < 0)
				return (res * -1);
		}
		i++;
	}
	return (0);
}
