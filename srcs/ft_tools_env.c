/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 13:39:49 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/02 16:14:11 by gadeneux         ###   ########.fr       */
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

static int	ft_inject(t_data **data, char *str, char **result)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		ft_char_writeon(&tmp, str[i]);
		i++;
	}
	if (ft_getenv(data, tmp))
	{
		ft_str_writeon(result, ft_getenv(data, tmp)->value);
	} else
	if (tmp)
	{
		free(tmp);
	}
	if (i == 0)
		ft_char_writeon(result, '$');
	return (i);
}

static void	ft_replace_env_on(t_data **data, char **str)
{
	char	*result;
	char	quote;
	int		i;

	i = 0;
	quote = 0;
	result = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
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
			else if ((*str)[i] == '$' && (!quote || quote != '\''))
			{
				i += ft_inject(data, &((*str)[i + 1]), &result);
			} else
				ft_char_writeon(&result, (*str)[i]);
		}
		i++;
	}
	if (!result)
		result = ft_strdup("");
	free(*str);
	*str = result;
}

void	ft_replace_env(t_data **data, t_elem *list)
{
	t_elem	*cursor;
	
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
}