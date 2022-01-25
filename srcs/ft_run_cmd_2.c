/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/25 18:12:05 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

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
		ft_run_execve_with_all_path(path, cmd_args);
		// if res of ft_run_execve_with_all_path is -2 malloc error
		// if res of ft_run_execve_with_all_path is -1 unkmown error
		// if res of ft_run_execve_with_all_path is 0 command not found
		// if res of ft_run_execve_with_all_path is 1 fonction executed
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

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;
