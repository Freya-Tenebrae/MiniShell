/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:37 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/05 16:22:06 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//    pour les output : 
//        si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//            ni nul et out->error devra etre NULL
//        si il y a une erreur elle devra etre mise dans out->error
//            (argument, fonction didn't exist, ...) et out->output devra etre 
//            set a NULL;

static void	ft_show_env(t_data **data)
{
	int			i;

	i = 0;
	while (((*data)->env)[i])
	{
		ft_putstr("export ");
		ft_putstr(((*data)->env)[i]->name);
		if (((*data)->env)[i]->value)
		{
			ft_putstr("=\"");
			ft_putstr(((*data)->env)[i]->value);
			ft_putstr("\"");
		}
		ft_putstr("\n");
		i++;
	}
}

static int	ft_fill(char **cmd_args, t_data **data)
{
	t_env	*variable;
	char	*name;
	int		i;

	i = 1;
	name = 0;
	while (cmd_args[i])
	{
		name = ft_str_before(cmd_args[i], '=');
		if (!name)
			return (0);
		variable = ft_create_variable(name, NULL);
		free(name);
		if (!variable)
			return (0);
		if (!ft_is_valid_variable_identifier(variable->name))
		{
			variable->name = ft_strdup(cmd_args[i]);
			if (!variable->name)
			{
				free(variable);
				return (-1);
			}
		}
		if (!ft_is_valid_variable_identifier(variable->name))
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(variable->name, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ft_free_variable(variable);
		}
		else
		{
			if (ft_str_indexof(cmd_args[i], '=') != -1)
				variable->value = ft_str_after(cmd_args[i], '=');
			if (!ft_add_variable(data, variable))
			{
				free(variable);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

void	ft_run_bi_export(t_data **data, char **cmd_args)
{
	if (!cmd_args || !cmd_args[1])
		return (ft_show_env(data));
	if (!ft_fill(cmd_args, data))
		ft_put_error(GENERIC_ERROR, "malloc error");
}
