/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 04:43:04 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/21 15:47:37 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_arg_is_numeric(char *arg)
{
	int	i;

	i = -1;
	if (ft_strlen(arg) >= 20)
		return (-1);
	if (ft_strcmp(arg, "-") == 0 || ft_strcmp(arg, "+") == 0)
		return (-1);
	while (arg[++i] != '\0')
	{
		if (ft_isdigit(arg[i]) == 0 && !(i == 0 && \
											(arg[i] == '-' || arg[i] == '+')))
			return (-1);
	}
	return (0);
}

static int	ft_get_number_args(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	return (i - 1);
}

static void	ft_update_minishell_status(char *exitcode)
{
	int	i;

	if (exitcode == NULL || *exitcode == '\0')
		i = g_status_minishell.status_pipe;
	else
		i = ft_atoi(exitcode) % 256;
	if (g_status_minishell.status_minishell != 2)
		g_status_minishell.status_minishell = -1;
	g_status_minishell.exitcode = i;
}

int	ft_run_bi_exit(char **cmd_args)
{
	int	nb_arg;

	if (!cmd_args || !*cmd_args)
		return (2);
	nb_arg = ft_get_number_args(cmd_args);
	if (cmd_args[1] && ft_arg_is_numeric(cmd_args[1]) != 0)
	{
		ft_update_minishell_status("2");
		ft_put_error_void(NUMERIC_ARG_NEEDED_ERROR, cmd_args[1]);
		return (1);
	}
	else if (nb_arg > 1)
	{
		ft_put_error_void(GENERIC_ERROR, "too mutch arguments");
		return (1);
	}
	ft_update_minishell_status(cmd_args[1]);
	return (g_status_minishell.exitcode);
}
