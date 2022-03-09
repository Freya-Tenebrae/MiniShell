/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:45:07 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/09 10:38:19 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_is_build_in(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "echoX") == 0 || ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || \
		ft_strcmp(cmd, "exit") == 0)
		return (1);
	else
		return (0);
}

int		ft_run_bi(t_data **data, char **cmd_args)
{
	if (cmd_args[0] == NULL)
		return (0);
	if (ft_strcmp(cmd_args[0], "echo") == 0)
		return (ft_run_bi_echo(cmd_args));
	else if (ft_strcmp(cmd_args[0], "cd") == 0)
		return (ft_run_bi_cd(data, cmd_args));
	else if (ft_strcmp(cmd_args[0], "pwd") == 0)
		return (ft_run_bi_pwd());
	else if (ft_strcmp(cmd_args[0], "export") == 0)
		return (ft_run_bi_export(data, cmd_args));
	else if (ft_strcmp(cmd_args[0], "unset") == 0)
		return (ft_run_bi_unset(data, cmd_args));
	else if (ft_strcmp(cmd_args[0], "env") == 0)
		return (ft_run_bi_env(data));
	else if (ft_strcmp(cmd_args[0], "exit") == 0)
		return (ft_run_bi_exit(cmd_args));
	return (0);
}
