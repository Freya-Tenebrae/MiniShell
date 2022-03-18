/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_is_executable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/18 14:43:44 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_if_slash_exist_test_dir(char *cmd)
{
	struct stat	*statbuf;

	statbuf = malloc(sizeof(struct stat));
	if (!statbuf || statbuf == NULL)
		return (-1);
	stat(cmd, statbuf);
	if ((statbuf->st_mode & S_IFMT) == S_IFDIR)
	{
		free(statbuf);
		return (-4);
	}
	else
	{
		free(statbuf);
		return (1);
	}
}

int	ft_if_slash_exist(char *cmd)
{
	int			i;

	i = -1;
	while (cmd[++i] != '\0')
	{
		if (cmd[i] == '/')
		{
			if (access(cmd, F_OK) != 0)
				return (-2);
			else if (access(cmd, X_OK) != 0)
				return (-3);
			else
			{
				return (ft_if_slash_exist_test_dir(cmd));
			}
		}
	}
	return (0);
}
