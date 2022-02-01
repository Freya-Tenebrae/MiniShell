/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_cmd_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/01 17:53:36 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

/* Éxecute une commande en prenant (ou non) un input d'une commande */
/* précédente */
/* Il renvoie un t_output qui contient la sortie stdout et stderr. */

static int	ft_init_var(t_output **res, int (*stdout)[2], int (*stderr)[2])
{
	*res = malloc(sizeof(t_output));
	if (!*res)
		return (-1);
	(*res)->output = NULL;
	(*res)->error = NULL;
	if (pipe(*stdout) == -1)
		return (-1);
	if (pipe(*stderr) == -1)
		return (-1);
	return (0);
}

t_output	*ft_exec_cmd(char *path, char **cmd_args, char *infile)
{
	t_output	*res;
	int			stdout[2];
	int			stderr[2];
	int			input[2];
	int			pid;
	int			pid2;
	int			result_execve;
	char		c;

	if (ft_init_var(&res, &stdout, &stderr) != 0)
		return (NULL);
	pid = fork();
	if (pid == 0)
	{
		close(stdout[0]);
		close(stderr[0]);
		if (infile != NULL)
		{
			if (pipe(input) == -1)
				return (0);
			pid2 = fork();
			if (pid2 == 0)
			{
				close(stdout[1]);
				close(stderr[1]);
				ft_putstr_fd(infile, input[1]);
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
		result_execve = ft_run_execve_with_all_path(path, cmd_args);
		if (result_execve == 0)
		{
			ft_putstr_fd("minishell : ", stderr[1]);
			ft_putstr_fd(cmd_args[0], stderr[1]);
			ft_putstr_fd(" : commande introuvable\n", stderr[1]);
		}
		else if (result_execve == -1)
			ft_putstr_fd("malloc error", stderr[1]);
		dup2(stderr[1], STDERR_FILENO);
		close(stderr[1]);
		exit(0);
	}
	else
	{
		close(stdout[1]);
		close(stderr[1]);
		while (read(stdout[0], &c, sizeof(char)))
			ft_char_writeon(&res->output, c);
		while (read(stderr[0], &c, sizeof(char)))
			ft_char_writeon(&res->error, c);
		if (!res->output && !res->error)
			res->output = ft_strdup("");
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
