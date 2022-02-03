/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:39:49 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/03 15:00:50 by cmaginot         ###   ########.fr       */
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
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (g_minishell->env[i])
	{
		if (ft_strcmp(g_minishell->env[i]->name, str) == 0)
			return (g_minishell->env[i]);
		i++;
	}
	return (0);
}

/* Remplace dans str les variables d'environnement */

static void	ft_replace_env_p2(char *str, int *i, char **res)
{
	char	*var;
	t_env	*variable;
	int		j;

	var = NULL;
	variable = NULL;
	j = *i + 1;
	while ((str)[j] && (ft_isalnum((str)[j]) || (str)[j] == '_'))
	{
		ft_char_writeon(&var, (str)[j]);
		if (ft_getenv(var) != 0)
			variable = ft_getenv(var);
		j++;
	}
	if (var)
	{
		variable = ft_getenv(var);
		if (variable)
			ft_str_writeon(res, variable->value);
		*i += (int) ft_strlen(var) + 1;
		var = 0;
	}
}

static void	ft_replace_env_p1(char *str, int *i, char **res)
{
	char	quote;

	quote = 0;
	if ((str)[*i] == '$' && ft_isquote((str)[*i + 1]) && !quote)
		*i += 1;
	if (!quote && ft_isquote((str)[*i]))
		quote = (str)[*i];
	else if (quote && (str)[*i] == quote)
		quote = 0;
	else if ((str)[*i] == '$' && (!quote || quote != '\''))
	{
		ft_replace_env_p2(str, i, res);
	}
	ft_char_writeon(res, (str)[*i]);
	*i += 1;
}

void	ft_replace_env(char **str)
{
	int		i;
	int		strlen;
	char	*res;

	if (!str || !*str)
		return ;
	i = 0;
	strlen = ft_strlen(*str);
	res = NULL;
	while (i < strlen && (*str)[i])
		ft_replace_env_p1(*str, &i, &res);
	free(*str);
	*str = res;
}
