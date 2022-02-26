/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/26 19:55:52 by gadeneux         ###   ########.fr       */
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

static int	ft_run_execve_with_one_path(char **cmd_args, char *path)
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
	execve(clone[0], clone, NULL);
	ft_freestrs(&clone);
	return (0);
}

int	ft_run_execve_with_all_path(char *path, char **cmd_args)
{
	char	**paths;
	int		i;
	int		res_one_path;

	paths = ft_split(path, ':');
	i = 0;
	if (!paths)
		return (0);
	while (paths[i] != NULL)
	{
		res_one_path = ft_run_execve_with_one_path(cmd_args, paths[i]);
		if ((res_one_path) != 0)
		{
			ft_freestrs(&paths);
			return (res_one_path);
		}
		else
			i++;
	}
	ft_freestrs(&paths);
	return (0);
}
