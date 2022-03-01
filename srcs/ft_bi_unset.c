/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:52 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/01 12:10:31 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;

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

int		ft_str_equal(char *s1, char *s2)
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
		return (0);
	while ((*data)->env[i])
	{
		if (!ft_str_equal((*data)->env[i]->name, identifier))
		{
			res[j] = ft_clone_variable((*data)->env[i]);
			if (!res[j])
			{
				ft_free_env(res);
				return (0);
			}
			j++;
		}
		i++;
	}
	res[j] = 0;
	return (res);
}

int		ft_unset_env(t_data **data, char *identifier)
{
	t_env	**copy;
	
	if (!identifier || !ft_getenv(data, identifier))
		return (1);
	copy = ft_clone_without_env(data, identifier);
	if (!copy)
		return (0);
	ft_free_env((*data)->env);
	(*data)->env = copy;
	return (1);
}

int		ft_read_unset(t_data **data, t_output *res, char **cmd_args)
{
	int		i;

	i = 1;
	while (cmd_args[i])
	{
		if (!ft_is_valid_identifier(cmd_args[i]))
		{
			res->output = NULL;
			ft_str_writeon(&res->error, "minishell: unset: `");
			ft_str_writeon(&res->error, cmd_args[i]);
			ft_str_writeon(&res->error, "': not a valid identifier\n");
		} else {
			ft_unset_env(data, cmd_args[i]);
		}
		i++;
	}
	return (1);
}

t_output	*ft_run_bi_unset(t_data **data, char **cmd_args)
{
	t_output	*res;

	res = malloc(sizeof(t_output));
	if (!res)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (0);
	}
	res->error = 0;
	res->output = 0;
	if (!cmd_args || !cmd_args[1])
		return (res);
	ft_read_unset(data, res, cmd_args);
	if (!res->error)
	{
		res->error = NULL;
		res->output = ft_strdup("");
		if (!res->output)
		{
			free(res);
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (0);
		}
	}
	return (res);
}
