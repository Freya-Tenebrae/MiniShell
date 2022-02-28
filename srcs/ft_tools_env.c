/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:39:49 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/27 21:29:06 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Renvoie un tableau de t_env depuis l'envp. */

void	ft_free_envs(t_env ***env, int i)
{
	while (i >= 0)
	{
		if ((*env)[i] && (*env)[i] != NULL)
		{
			ft_free_env(&((*env)[i]));
			//free((*env)[i]);
		}
		i--;
	}
	free(*env);
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
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (0);
	}
	i = 0;
	while (envp[i])
	{
		res[i] = malloc(sizeof(t_env));
		if (!res[i])
		{
			ft_free_envs(&res, i - 1);
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (NULL);
		}
		res[i]->name = ft_str_before(envp[i], '=');
		if (!res[i]->name || res[i]->name == NULL)
		{
			free(res[i]);
			ft_free_envs(&res, i - 1);
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (NULL);
		}
		res[i]->value = ft_str_after(envp[i], '=');
		if (!res[i]->value || res[i]->value == NULL)
		{
			free(res[i]->name);
			free(res[i]);
			ft_free_envs(&res, i - 1);
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (NULL);
		}
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

static void	ft_remove_quotes(t_elem *list)
{
	char	*buffer;

	while (list)
	{
		buffer = ft_keepinside_quote(list->str);
		free(list->str);
		list->str = buffer;
		list = list->next;
	}
}

static	void ft_replace_env_on(t_data **data, char **str)
{
    char    quote;
    char    *res;
    char    *var;
    int        i;
    int        j;
    t_env * variable;

    i = 0;
    var = 0;
    res = NULL;
    quote = 0;
    variable = NULL;
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
        {
            if (quote && (*str)[i] == quote)
                quote = 0;
            else
            {
                if ((*str)[i] == '$' && (!quote || quote != '\''))
                {
                    j = i + 1;
                    while ((*str)[j] && (ft_isalnum((*str)[j]) || (*str)[j] == '_'))
                    {
                        ft_char_writeon(&var, (*str)[j]);
                        if (!var || var == NULL)
                        {
                            ft_put_error(GENERIC_ERROR, "malloc error");
                            ft_put_error(GENERIC_ERROR, "environnement error");
                            return ;
                        }
                        if (ft_getenv(data, var) != 0)
                        {
                            variable = ft_getenv(data, var);
                            if (!variable || variable == NULL)
                            {
                                ft_put_error(GENERIC_ERROR, "malloc error");
                                ft_put_error(GENERIC_ERROR, "environnement error");
                                return ; // erreur susceptible de faire crash
                            }
                        }
                        j++;
                    }
                    if (var)
                    {
                        variable = ft_getenv(data, var);
                        if (!variable || variable == NULL)
                        {
                            ft_put_error(GENERIC_ERROR, "environnement error");
                            return ;
                        }
                        ft_str_writeon(&res, variable->value);
                        if (!res || res == NULL)
                        {
                            ft_put_error(GENERIC_ERROR, "malloc error");
                            ft_put_error(GENERIC_ERROR, "environnement error");
                            return ;
                        }
                        i += (int) ft_strlen(var) + 1;
                        var = 0;
                        continue ;
                    }
                }
            }
        }
        ft_char_writeon(&res, (*str)[i]);
        if (!res || res == NULL)
        {
            ft_put_error(GENERIC_ERROR, "malloc error");
            ft_put_error(GENERIC_ERROR, "environnement error");
            return ;
        }
        i++;
    }
    free(*str);
    *str = res;
}

void	ft_replace_env(t_data **data, t_elem *list)
{
	t_elem	*cursor;
	
	(void) data;
	cursor = list;
	while (cursor)
	{
		if (cursor->type == DOUBLE_IN)
		{
			cursor = cursor->next->next;
			continue ;
		}
		ft_replace_env_on(data, &(cursor->str));
		cursor = cursor->next;
	}
	ft_remove_quotes(list);
}