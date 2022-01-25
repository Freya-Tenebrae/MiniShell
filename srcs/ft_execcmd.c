/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execcmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/24 17:37:56 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Éxecute une commande */

int	ft_execute_cmd(char *path, char **cmd_args)
{
	int		i;
	char	**paths;
	char	**clone;
	char	*label;

	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return (0);
	while (paths[i])
	{
		clone = ft_str_clonetab(cmd_args);
		label = 0;
		if (!clone)
		{
			ft_freestrs(&paths);
			return (0);
		}
		ft_str_writeon(&label, paths[i]);
		ft_char_writeon(&label, '/');
		ft_str_writeon(&label, cmd_args[0]);
		free(clone[0]);
		clone[0] = label;
		if (execve(clone[0], clone, NULL) != -1)
		{
			ft_freestrs(&clone);
			ft_freestrs(&paths);
			return (1);
		}
		ft_freestrs(&clone);
		i++;
	}
	ft_freestrs(&paths);
	return (0);
}

/* Éxecute une commande en prenant (ou non) un input d'une commande */
/* précédente */
/* Il renvoie un t_output qui contient la sortie stdout et stderr. */

t_output	*ft_exec_cmd(char *path, char **cmd_args, char *infile)
{
	t_output	*res;
	int			stdout[2];
	int			stderr[2];
	int			input[2];
	int			pid;
	int			pid2;
	char		c;

	res = malloc(sizeof(t_output));
	if (!res)
		return (0);
	res->output = 0;
	res->error = 0;
	if (pipe(stdout) == -1)
		return (0);
	if (pipe(stderr) == -1)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		close(stdout[0]);
		close(stderr[0]);
		if (infile)
		{
			if (pipe(input) == -1)
				return (0);
			pid2 = fork();
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
		// if ft_execute_cmd == 0 put an error command not found
		//else continue
		exit(0);
		return (0);
	}
	else
	{
		close(stdout[1]);
		close(stderr[1]);
		while (read(stdout[0], &c, sizeof(char)))
			ft_char_writeon(&res->output, c);
		while (read(stderr[0], &c, sizeof(char)))
			ft_char_writeon(&res->error, c);
		// solution temporaire pour eviter les SGV lies a output et error vide
		if (!res->output && !res->error)
		{
			res->output = ft_strdup("");
		}
		// fin de la solution temporaire
		// il y a un bug qui fait que le systeme ne repaire pas si une fonction 
		// 		n'existe pas
		// il est aussi necessaire de replir stdout d;une chaine de caractere
		// 		vide lorsce que une fonction ne donne pas de sortie
		//		(ex "ls test",avec l'argument "test" un chemin vers un
		//		dossier vide)
	}
	waitpid(pid, 0, 0);
	close(stdout[0]);
	close(stderr[0]);
	return (res);
}
