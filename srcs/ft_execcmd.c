/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/12 17:16:05 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Éxecute une commande */

int	ft_execute_cmd(char *path, char **cmd_args)
{
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		char **clone = ft_str_clonetab(cmd_args);
		char *label = 0;
		
		if (!clone)
		{
			free(paths);
			return (0);
		}
		
		ft_str_writeon(&label, paths[i]);
		ft_char_writeon(&label, '/');
		ft_str_writeon(&label, cmd_args[0]);
		
		free(clone[0]);
		clone[0] = label;
		
		if (execve(clone[0], clone, NULL) != -1)
		{
			ft_str_freetab(clone);
			free(paths);
			return (1);
		}
		ft_str_freetab(clone);
		i++;
	}
	free(paths);
	return (0);
}

/* Éxecute une commande en prenant (ou non) un input d'une commande précédente */
/* Il renvoie un t_output qui contient la sortie stdout et stderr. */

t_output    *ft_run_cmd(char *path, char **cmd_args, char *infile)
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
		
        ft_execute_cmd(path, cmd_args);
        exit(0);
        return (0);
    } else {
        close(stdout[1]);
        close(stderr[1]);
        
		char c;
		while (read(stdout[0], &c, sizeof(char)))
			ft_char_writeon(&res->output, c);
		while (read(stderr[0], &c, sizeof(char)))
			ft_char_writeon(&res->error, c);
    }
    waitpid(pid, 0, 0);
    close(stdout[0]);
    close(stderr[0]);
    return (res);
}
