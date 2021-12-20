/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2021/12/20 02:45:33 by gadeneux         ###   ########.fr       */
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

void	ft_freetab(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

char	**ft_clonetab(char **strs)
{
	int len = 0;
	while (strs[len])
		len++;
	char **res = malloc(sizeof(char*) * (len + 1));
	if (!res)
		return (0);
	int i = 0;
	while (strs[i])
	{
		res[i] = ft_strdup(strs[i]);
		i++;
	}
	res[i] = NULL;
	return (res);
}

int	ft_execcmd(char *path, char **cmd_args)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		char **clone = ft_clonetab(cmd_args);
		char *label = 0;
		
		if (!clone)
		{
			free(paths);
			return (0);
		}
		
		ft_writestr_on(&label, paths[i]);
		ft_writechar_on(&label, '/');
		ft_writestr_on(&label, cmd_args[0]);
		
		free(clone[0]);
		clone[0] = label;
		
		if (execve(clone[0], clone, NULL) != -1)
		{
			ft_freetab(clone);
			free(paths);
			return (1);
		}
		ft_freetab(clone);
		i++;
	}
	free(paths);
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

char	*ft_runcmd(char *path, char **cmd_args, char *infile)
{
	char	*res;
	int		fd[2];

	res = 0;
	if (pipe(fd) == -1)
		return (0);
		
	int pid = fork();
	if (pid == 0)
	{
		close(fd[0]);

		if (infile)
		{
			int	input[2];
			if (pipe(input) == -1)
				return (0);
			int pid2 = fork();
			if (pid2 == 0)
			{
				close(fd[0]);
				close(fd[1]);
				write(input[1], infile, ft_strlen(infile));
				exit(0);
			}
			close(input[1]);
			waitpid(pid2, 0, 0);
			dup2(input[0], STDIN_FILENO);
			close(input[0]);
		}

		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		
		ft_execcmd(path, cmd_args);
		close(STDOUT_FILENO);
		return (0);
	} else {
		close(fd[1]);
		int ret = 0;
		char *tmp = 0;
		while ((ret = get_next_line(fd[0], &tmp)))
		{
			ft_writestr_on(&res, tmp);
			ft_writechar_on(&res, '\n');
			// printf("\"%s\"\n", tmp);
		}
		close(fd[0]);
	}
	waitpid(pid, 0, 0);
	close(fd[0]);
	close(fd[1]);
	return (res);
}
