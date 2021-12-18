/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2021/12/18 21:29:45 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

// static int	__ft_execcmd(char ***args, int *i, char **cmd_args, char **cmd)
// {
// 	if (*args)
// 	{
// 		while ((*args)[*i])
// 		{
// 			cmd_args = ft_split(*cmd, ' ');
// 			if (cmd_args)
// 			{
// 				free(cmd_args[0]);
// 				cmd_args[0] = ft_join(ft_join(ft_strdup((*args)[*i]),
// 							ft_strdup("/")), ft_before(*cmd));
// 				if (execve(cmd_args[0], cmd_args, NULL) != -1)
// 				{
// 					ft_free(cmd_args);
// 					ft_free(*args);
// 					return (1);
// 				}
// 				ft_free(cmd_args);
// 			}
// 			(*i)++;
// 		}
// 		ft_free(*args);
// 	}
// 	return (0);
// }

// int	ft_execcmd(char *path, char **cmd_args, char *cmd)
// {
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = ft_split(path, ':');
// 	if (__ft_execcmd(&args, &i, cmd_args, &cmd) == 1)
// 		return (1);
// 	return (0);
// }

// char	*ft_getpath(char **envp)
// {
// 	char	*dst;

// 	dst = 0;
// 	while (*envp)
// 	{
// 		if (ft_strncmp(*envp, "PATH=", 5) == 0)
// 		{
// 			dst = ft_strdup(*envp + 5);
// 			break ;
// 		}
// 		envp++;
// 	}
// 	return (dst);
// }