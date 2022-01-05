/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2021/12/24 12:27:40 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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

t_output    *ft_runcmd(char *path, char **cmd_args, char *infile)
{
	t_output	*res;
	
    int		stdout[2];
    int		stderr[2];
    
    res = malloc(sizeof(t_output));
	if (!res)
		return (0);
	res->output = 0;
	res->error = 0;
	if (pipe(stdout) == -1)
        return (0);
    if (pipe(stderr) == -1)
        return (0);
	
    int pid = fork();
    if (pid == 0)
    {
        close(stdout[0]);
        close(stderr[0]);
       	
		if (infile)
        {
            int input[2];
            if (pipe(input) == -1)
                return (0);
            int pid2 = fork();
            if (pid2 == 0)
            {
                close(stdout[1]);
				close(stderr[1]);
                write(input[1], infile, ft_strlen(infile));
                exit(0);
            }
            close(input[1]);
            waitpid(pid2, 0, 0);
            dup2(input[0], STDIN_FILENO);
            close(input[0]);
        }
        
		dup2(stdout[1], STDOUT_FILENO);
        close(stdout[1]);
		dup2(stderr[1], STDERR_FILENO);
        close(stderr[1]);
		
        ft_execcmd(path, cmd_args);
        exit(0);
        return (0);
    } else {
        close(stdout[1]);
        close(stderr[1]);
        
		char c;
		while (read(stdout[0], &c, sizeof(char)))
			ft_writechar_on(&res->output, c);
		while (read(stderr[0], &c, sizeof(char)))
			ft_writechar_on(&res->error, c);
    }
    waitpid(pid, 0, 0);
    close(stdout[0]);
    close(stderr[0]);
    return (res);
}
