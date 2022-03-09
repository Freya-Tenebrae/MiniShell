/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:20 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/09 17:19:17 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_has_nl_option(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (ft_strlen(str) == 0)
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		return (1);
		i++;
	}
	return (0);
}

int	ft_is_valid_option(char *str)
{
	int	i;

	i = 0;
	if (!str || ft_strlen(str) < 1)
		return (0);
	if (!str[i] || str[i] != '-')
		return (0);
	i++;
	while (str[i])
		if (str[i++] != 'n')
			return (0);
	return (1);
}

int	ft_run_bi_echo(char **cmd_args)
{
	int			no_nl;
	int			i;

	if (!cmd_args || !*cmd_args)
		return (2);
	no_nl = 0;
	i = 1;
	while (cmd_args[i] && ft_is_valid_option(cmd_args[i]))
	{
		if (ft_has_nl_option(cmd_args[i]))
			no_nl = 1;
		i++;
	}
	while (cmd_args[i])
	{
		ft_putstr(cmd_args[i]);
		i++;
		if (cmd_args[i])
			ft_putchar((char) 32);
	}
	if (no_nl == 0)
		ft_putchar('\n');
	return (0);
}
