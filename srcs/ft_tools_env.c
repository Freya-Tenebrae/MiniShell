/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:39:49 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/10 11:02:26 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Renvoie un tableau de t_env depuis l'envp. */

int	ft_get_size_env(t_env ***env)
{
	int	i;

	i = 0;
	while ((*env)[i] && (*env)[i] != NULL)
	{
		i++;
	}
	return (i - 1);
}

void	ft_free_envs(t_env ***env, int i)
{
	while (i >= 0)
	{
		if ((*env)[i] && (*env)[i] != NULL)
		{
			ft_free_env(&((*env)[i]));
		}
		i--;
	}
	free(*env);
}

static int	ft_init_env_loop(char **envp, int i, t_env ***res)
{
	(*res)[i] = malloc(sizeof(t_env));
	if (!(*res)[i])
	{
		ft_free_envs(&(*res), i - 1);
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	(*res)[i]->name = ft_str_before(envp[i], '=');
	if (!(*res)[i]->name || (*res)[i]->name == NULL)
	{
		free((*res)[i]);
		ft_free_envs(&(*res), i - 1);
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	(*res)[i]->value = ft_str_after(envp[i], '=');
	if (!(*res)[i]->value || (*res)[i]->value == NULL)
	{
		free((*res)[i]->name);
		free((*res)[i]);
		ft_free_envs(&(*res), i - 1);
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	return (0);
}

t_env	**ft_init_env(char **envp)
{
	t_env	**res;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	res = malloc(sizeof(t_env) * (i + 1));
	if (!res)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	i = 0;
	while (envp[i])
	{
		if (ft_init_env_loop(envp, i, &res) == -1)
			return (NULL);
		i++;
	}
	res[i] = 0;
	return (res);
}

/* Récupère la variable d'environnement associé au nom str, ou un pointeur */
/* sur nul sur la variable n'existe pas. */

t_env	*ft_getenv(t_data **data, char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while ((*data)->env[i])
	{
		if (ft_strcmp((*data)->env[i]->name, str) == 0)
			return ((*data)->env[i]);
		i++;
	}
	return (NULL);
}
