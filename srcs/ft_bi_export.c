/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:37 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/11 14:47:24 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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
	int		i;
	char	*tmp;

	i = 1;
	while (cmd_args[i])
	{
		if (ft_str_indexof(cmd_args[i], '=') == -1)
		{
			if (!ft_is_valid_variable_identifier(cmd_args[i]))
				ft_put_error(IDENTIFIER_VAR_ERROR, cmd_args[i]);
			else
				ft_create_or_update_variable(data, cmd_args[i], NULL);
		}
		else
		{
			tmp = ft_str_before(cmd_args[i], '=');
			if (!tmp)
				return (-1);
			if (!ft_is_valid_variable_identifier(tmp))
				ft_put_error(IDENTIFIER_VAR_ERROR, cmd_args[i]);
			else
				ft_create_or_update_variable(data, tmp, \
											ft_str_after(cmd_args[i], '='));
			free(tmp);
		}
		i++;
	}
	return (1);
}

int	ft_run_bi_export(t_data **data, char **cmd_args)
{
	if (!cmd_args || !*cmd_args)
	{
		ft_show_env(data);
		return (2);
	}
	if (!cmd_args[1])
	{
		ft_show_env(data);
		return (0);
	}
	if (!ft_fill(cmd_args, data))
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (2);
	}
	return (0);
}
