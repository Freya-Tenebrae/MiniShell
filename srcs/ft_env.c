/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:39:49 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/12 17:25:50 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Renvoie un tableau de t_env depuis l'envp. */

t_env	**ft_init_env(char **envp)
{
	t_env	**res;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	res = malloc(sizeof(t_env) * (i + 1));
	if (!res)
		return (0);
	i = 0;
	while (envp[i])
	{
		res[i] = malloc(sizeof(t_env));
		if (!res[i])
			return (0);
		res[i]->name = ft_str_before(envp[i], '=');
		res[i]->value = ft_str_after(envp[i], '=');
		i++;
	}
	res[i] = 0;
	return (res);
}

/* Récupère la variable d'environnement associé au nom str, ou un pointeur */
/* sur nul sur la variable n'existe pas. */

t_env	*ft_getenv(char *str)
{
	int i = 0;
	if (!str)
		return (0);
	while (minishell->env[i])
	{
		if (ft_strcmp(minishell->env[i]->name, str) == 0)
			return (minishell->env[i]);
		i++;
	}
	return (0);
}

/* Remplace dans str les variables d'environnement */

void	ft_replace_env(char **str)
{
	char	quote;
	char	*res;
	char	*var;
	int		i;
	
	i = 0;
	var = 0;
	res = 0;
	quote = 0;
	if (!str || !*str)
		return ;
	while (i < (int) ft_strlen(*str) && (*str)[i])
	{
		if ((*str)[i] == '$' && ft_isquote((*str)[i + 1]) && !quote)
		{
			i++;
			continue ;
		}
		if (!quote && ft_isquote((*str)[i]))
			quote = (*str)[i];
		else
		if (quote && (*str)[i] == quote)
			quote = 0;
		else
		if ((*str)[i] == '$' && (!quote || quote != '\''))
		{
			int j = i + 1;
			t_env *variable = 0;
			while ((*str)[j] && (ft_isalnum((*str)[j]) || (*str)[j] == '_'))
			{
				ft_char_writeon(&var, (*str)[j]);
				if (ft_getenv(var) != 0)
					variable = ft_getenv(var);
				j++;
			}
			if (var)
			{
				variable = ft_getenv(var);
				if (variable)
					ft_str_writeon(&res, variable->value);
				i += (int) ft_strlen(var) + 1;
				var = 0;
				continue ;	
			}
		}
		ft_char_writeon(&res, (*str)[i]);
		i++;
	}
	free(*str);
	*str = res;
}
