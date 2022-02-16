/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:37 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/16 18:00:09 by gadeneux         ###   ########.fr       */
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
		ft_str_writeon(&res->output, "=\"");
		ft_str_writeon(&res->output, ((*data)->env)[i]->value);
		ft_str_writeon(&res->output, "\"\n");
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

void	ft_add_variable(t_data **data, char *identifier, char *value)
{
	(void) data;
	ft_putstr(identifier);
	ft_putstr(":'");
	if (value)
		ft_putstr(value);
	ft_putstr("'\n");
}

void	ft_fill(t_output *res, char **cmd_args, t_data **data)
{
	char		*identifier;
	int			i;
	
	i = 1;
	while (cmd_args[i])
	{
		identifier = ft_str_before(cmd_args[i], '=');
		if (!identifier || ft_strlen(identifier) == 0)
		{
			free(identifier);
			identifier = ft_strdup(cmd_args[i]);
		}
		if (!ft_is_valid_identifier(identifier))
		{
			res->output = NULL;
			ft_str_writeon(&res->error, "minishell: export: `");
			ft_str_writeon(&res->error, identifier);
			ft_str_writeon(&res->error, "': not a valid identifier\n");
		}
		else
		{
			if (ft_str_indexof(cmd_args[i], '=') != -1)
				ft_add_variable(data, identifier, ft_str_after(cmd_args[i], '='));
			else
				ft_add_variable(data, identifier, 0);
		}
		i++;
	}
}

t_output	*ft_run_bi_export(t_data **data, char *path, char **cmd_args, char *infile)
{
	t_output	*res;

	(void)path;
	(void)infile;
	if (!cmd_args || !cmd_args[1])
		return (ft_show_env(data));
	res = malloc(sizeof(t_output));
	if (!res)
		return (0);
	res->error = 0;
	res->output = 0;
	ft_fill(res, cmd_args, data);
	if (!res->error)
	{
		res->output = ft_strdup("");
		res->error = NULL;
		if (!res->output)
		{
			free(res);
			return (0);
		}
	}
	return (res);
}