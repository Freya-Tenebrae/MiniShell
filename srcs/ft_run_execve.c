/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/12 15:01:43 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Éxecute une commande */

static int	ft_check_if_label_is_not_null(char *label, char ***clone)
{
	if (label == NULL)
	{
		ft_freestrs(clone);
		return (-1);
	}
	return (0);
}

static int	ft_run_execve_with_one_path(char **cmd_args, char *path, \
																char ***envp)
{
	char	**clone;
	char	*label;

	clone = ft_str_clonetab(cmd_args);
	if (!clone)
		return (-1);
	label = NULL;
	ft_str_writeon(&label, path);
	if (ft_check_if_label_is_not_null(label, &clone) != 0)
		return (-1);
	ft_char_writeon(&label, '/');
	if (ft_check_if_label_is_not_null(label, &clone) != 0)
		return (-1);
	ft_str_writeon(&label, cmd_args[0]);
	if (ft_check_if_label_is_not_null(label, &clone) != 0)
		return (-1);
	free(clone[0]);
	clone[0] = label;
	execve(clone[0], clone, *envp);
	ft_freestrs(&clone);
	return (0);
}

static int	ft_run_execve_for_exec(char **cmd_args, char ***paths, char ***envp)
{
	ft_freestrs(paths);
	execve(cmd_args[0], cmd_args, *envp);
	return (0);
}

static int	ft_run_execve_loop_path(char **cmd_args, char ***paths, int i, \
																char ***envp)
{
	int	res_one_path;

	res_one_path = ft_run_execve_with_one_path(cmd_args, (*paths)[i], envp);
	if ((res_one_path) != 0)
	{
		ft_freestrs(paths);
		return (res_one_path);
	}
	return (0);
}

int	ft_run_execve_with_all_path(char *path, char **cmd_args, t_data **data)
{
	int		res_one_path;
	char	**paths;
	char	**envp;
	int		i;

	if (!cmd_args || cmd_args == NULL || !cmd_args[0] || cmd_args[0] == NULL)
		return (-1);
	if (ft_if_slash_exist(cmd_args[0]) != 0)
		return (ft_if_slash_exist(cmd_args[0]));
	paths = ft_split(path, ':');
	i = 0;
	envp = (*data)->envp;
	if (!paths)
		return (0);
	while (paths[i] != NULL)
	{
		res_one_path = ft_run_execve_loop_path(cmd_args, &paths, i, &envp);
		if (res_one_path != 0)
			return (res_one_path);
		i++;
	}
	return (ft_run_execve_for_exec(cmd_args, &paths, &envp));
}
