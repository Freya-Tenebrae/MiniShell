/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:45:07 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/04 05:03:08 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_tools_is_build_in(char *cmd)
{
	if (cmd == NULL)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0)
		return (0);
	else
		return (1);
}

static t_output	*ft_put_empty_output(void)
{
	t_output	*out;

	out = malloc(sizeof(t_output));
	if (!out)
	{
		ft_tools_put_error(GENERIC_ERROR, "Malloc error");
		return (NULL);
	}
	out->error = NULL;
	out->output = ft_strdup("");
	if (!out->output)
	{
		ft_tools_put_error(GENERIC_ERROR, "Malloc error");
		ft_tools_free_output(&out);
		return (NULL);
	}
	return (out);
}

t_output	*ft_run_bi(char *path, char **cmd_args, char *infile)
{
	if (cmd_args[0] == NULL)
		return (ft_put_empty_output());
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
