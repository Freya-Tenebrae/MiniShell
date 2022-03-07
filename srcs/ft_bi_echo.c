/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:20 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/07 14:17:54 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;

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

void	ft_run_bi_echo(char **cmd_args)
{
	int			no_nl;
	int			i;

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
}
