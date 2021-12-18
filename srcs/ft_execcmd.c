/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2021/12/18 21:48:40 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

char	*ft_before(char *str)
{
	char	*dst;
	int		l;
	int		i;

	if (!str)
		return (0);
	l = 0;
	while (str[l] && str[l] != (char) 32)
		++l;
	dst = malloc(l + 1);
	if (!dst)
		return (0);
	i = 0;
	while (str[i] && i < l)
	{
		dst[i] = str[i];
		++i;
	}
	dst[i] = 0;
	return (dst);
}

char	*ft_after(char *str)
{
	char	*dst;
	char	*ret;
	size_t	l;

	if (!str)
		return (0);
	l = 0;
	while (str[l] && str[l] != '\n')
		l++;
	if (!str[l])
	{
		free(str);
		return (0);
	}
	dst = malloc(ft_strlen(str) - l);
	ret = dst;
	if (!ret)
		return (0);
	while (str[++l] && l < ft_strlen(str))
		*dst++ = str[l];
	dst = 0;
	return (ret);
}

char	*ft_strfjoin(char *s1, char *s2)
{
	char	*dst;

	dst = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	if (!dst)
		return (0);
	return (dst);
}

void	ft_freetab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

static int	__ft_execcmd(char ***args, int *i, char **cmd)
{
	char **cmd_args;
	if (*args)
	{
		while ((*args)[*i])
		{
			cmd_args = ft_split(*cmd, ' ');
			if (cmd_args)
			{
				free(cmd_args[0]);
				cmd_args[0] = ft_strfjoin(ft_strfjoin(ft_strdup((*args)[*i]), ft_strdup("/")), ft_before(*cmd));
				if (execve(cmd_args[0], cmd_args, NULL) != -1)
				{
					ft_freetab(cmd_args);
					ft_freetab(*args);
					return (1);
				}
				ft_freetab(cmd_args);
			}
			(*i)++;
		}
		ft_freetab(*args);
	}
	return (0);
}

int	ft_execcmd(char *path, char *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = ft_split(path, ':');
	if (__ft_execcmd(&args, &i, &cmd) == 1)
		return (1);
	return (0);
}

char	*ft_getpath(char **envp)
{
	char	*dst;

	dst = 0;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			dst = ft_strdup(*envp + 5);
			break ;
		}
		envp++;
	}
	return (dst);
}