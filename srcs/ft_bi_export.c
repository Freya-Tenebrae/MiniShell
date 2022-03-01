/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:37 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/01 12:09:47 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//    pour les output : 
//        si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//            ni nul et out->error devra etre NULL
//        si il y a une erreur elle devra etre mise dans out->error
//            (argument, fonction didn't exist, ...) et out->output devra etre 
//            set a NULL;

t_output	*ft_show_env(t_data **data)
{
	t_output	*res;
	int			i;

	i = 0;
	res = malloc(sizeof(t_output));
	if (!res)
		return (NULL);
	res->error = NULL;
	res->output = ft_strdup("");
	if (!res->output)
	{
		free(res);
		return (NULL);
	}
	while (((*data)->env)[i])
	{
		ft_str_writeon(&res->output, "export ");
		ft_str_writeon(&res->output, ((*data)->env)[i]->name);
		if (((*data)->env)[i]->value)
		{
			ft_str_writeon(&res->output, "=\"");
			ft_str_writeon(&res->output, ((*data)->env)[i]->value);
			ft_str_writeon(&res->output, "\"");
		}
		ft_str_writeon(&res->output, "\n");
		i++;
	}
	return (res);
}

int		ft_is_valid_identifier(char *str)
{
    int        i;

    i = 0;
    if (!str || ft_strlen(str) == 0)
        return (0);
    while (str[i])
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);    
        i++;
    }
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

t_env	*ft_create_variable(char *name, char *value)
{
	t_env	*res;

	res = malloc(sizeof(t_env));
	if (!res)
		return (0);
	res->name = name;
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
		return (0);
	value = 0;
	if (env->value)
	{
		value = ft_strdup(env->value);
		if (!value)
			return (0);
	}
	res = ft_create_variable(name, value);
	if (!res)
		return (0);
	return (res);
}

int		ft_env_tab_len(t_env **tab)
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
		return (0);
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

int		ft_try_replace(t_data **data, t_env *variable)
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
	free(variable);
	return (1);
}

int		ft_add_variable(t_data **data, t_env *variable)
{
	t_env	**copy;
	
	if (ft_try_replace(data, variable))
		return (1);

	copy = ft_clone_and_add_env((*data)->env, variable);
	if (!copy)
		return (0);

	ft_free_env((*data)->env);
	(*data)->env = copy;
	return (1);
}

int		ft_fill(t_output *res, char **cmd_args, t_data **data)
{
	t_env	*variable;
	int		i;

	i = 1;
	while (cmd_args[i])
	{
		variable = ft_create_variable(ft_str_before(cmd_args[i], '='), NULL);
		if (!variable)
			return (0);
		if (!ft_is_valid_identifier(variable->name))
			variable->name = ft_strdup(cmd_args[i]);
		if (!ft_is_valid_identifier(variable->name))
		{
			res->output = NULL;
			ft_str_writeon(&res->error, "minishell: export: `");
			ft_str_writeon(&res->error, variable->name);
			ft_str_writeon(&res->error, "': not a valid identifier\n");
			ft_free_variable(variable);
		}
		else
		{
			if (ft_str_indexof(cmd_args[i], '=') != -1)
				variable->value = ft_str_after(cmd_args[i], '=');
			if (!ft_add_variable(data, variable))
				return (0);
		}
		i++;
	}
	return (1);
}

t_output	*ft_run_bi_export(t_data **data, char **cmd_args)
{
	t_output	*res;

	if (!cmd_args || !cmd_args[1])
		return (ft_show_env(data));
	res = malloc(sizeof(t_output));
	if (!res)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (0);
	}
	res->error = 0;
	res->output = 0;
	if (!ft_fill(res, cmd_args, data))
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (0);
	}
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