/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:37 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/16 17:59:49 by cmaginot         ###   ########.fr       */
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

int	ft_run_bi_export(t_data **data, char **cmd_args)
{
	int		res;

	res = 0;
	if (!cmd_args || !*cmd_args)
		return (2);
	if (!cmd_args[1])
	{
		ft_show_env(data);
		return (0);
	}
	res = ft_fill(cmd_args, data);
	if (res == -1)
		return (1);
	else if (res == -2)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (2);
	}
	return (0);
}
