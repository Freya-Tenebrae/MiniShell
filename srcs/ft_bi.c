/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:45:07 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/03 15:00:39 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_tools_is_build_in(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0)
		return (0);
	else
		return (1);
}

t_output	*ft_run_bi(char *path, char **cmd_args, char *infile)
{
	if (ft_strcmp(cmd_args[0], "echo") == 0)
		return (ft_run_bi_echo(path, cmd_args, infile));
	else if (ft_strcmp(cmd_args[0], "cd") == 0)
		return (ft_run_bi_cd(path, cmd_args, infile));
	else if (ft_strcmp(cmd_args[0], "pwd") == 0)
		return (ft_run_bi_pwd(path, cmd_args, infile));
	else if (ft_strcmp(cmd_args[0], "export") == 0)
		return (ft_run_bi_export(path, cmd_args, infile));
	else if (ft_strcmp(cmd_args[0], "unset") == 0)
		return (ft_run_bi_env(path, cmd_args, infile));
	else if (ft_strcmp(cmd_args[0], "env") == 0)
		return (ft_run_bi_env(path, cmd_args, infile));
	return (NULL);
}
