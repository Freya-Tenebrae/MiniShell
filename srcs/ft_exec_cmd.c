/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 21:09:50 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/13 07:48:32 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_fill_stdin(char *infile, t_stdoutanderr **std_out_err)
{
	int	input[2];
	int	pid2;

	if (infile != NULL)
	{
		if (pipe(input) == -1)
			exit(0);
		pid2 = fork();
		if (pid2 == 0)
		{
			close((*std_out_err)->stdout[1]);
			close((*std_out_err)->stderr[1]);
			ft_putstr_fd(infile, input[1]);
			exit(0);
		}
		close(input[1]);
		waitpid(pid2, 0, 0);
		dup2(input[0], STDIN_FILENO);
		close(input[0]);
	}
}

static void	ft_exec_cmd_child(char *path, char **cmd_args, char *infile, \
								t_stdoutanderr **std_out_err)
{
	int	result_execve;

	close((*std_out_err)->stdout[0]);
	close((*std_out_err)->stderr[0]);
	ft_fill_stdin(infile, std_out_err);
	dup2((*std_out_err)->stdout[1], STDOUT_FILENO);
	close((*std_out_err)->stdout[1]);
	dup2((*std_out_err)->stderr[1], STDERR_FILENO);
	result_execve = ft_run_execve_with_all_path(path, cmd_args);
	if (result_execve == 0)
	{
		ft_putstr_fd("minishell : ", (*std_out_err)->stderr[1]);
		ft_putstr_fd(cmd_args[0], (*std_out_err)->stderr[1]);
		ft_putstr_fd(" : Command not found\n", (*std_out_err)->stderr[1]);
	}
	else if (result_execve == -1)
		ft_putstr_fd("malloc error", (*std_out_err)->stderr[1]);
	dup2((*std_out_err)->stderr[1], STDERR_FILENO);
	close((*std_out_err)->stderr[1]);
	exit(0);
}

static int	ft_init_var(t_output **res, t_stdoutanderr **std_out_err)
{
	*res = malloc(sizeof(t_output));
	if (!*res)
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	(*res)->output = NULL;
	(*res)->error = NULL;
	*std_out_err = malloc(sizeof(t_stdoutanderr));
	if (!*std_out_err)
	{
		ft_free_output(res);
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	if (pipe((*std_out_err)->stdout) == -1)
	{
		ft_free_output(res);
		free (*std_out_err);
		return (ft_put_error(GENERIC_ERROR, "pipe error"));
	}
	if (pipe((*std_out_err)->stderr) == -1)
	{
		ft_free_output(res);
		free (*std_out_err);
		return (ft_put_error(GENERIC_ERROR, "pipe error"));
	}
	return (0);
}

static t_output	*ft_free_output_co(t_output **res, t_stdoutanderr **std_out_err)
{
	ft_free_output(res);
	free (*std_out_err);
	return (NULL);
}

t_output	*ft_exec_cmd(char *path, char **cmd_args, char *infile)
{
	t_output		*res;
	t_stdoutanderr	*std_out_err;
	int				pid;

	if (ft_init_var(&res, &std_out_err) != 0)
		return (NULL);
	pid = fork();
	if (pid == 0)
		ft_exec_cmd_child(path, cmd_args, infile, &std_out_err);
	close(std_out_err->stdout[1]);
	close(std_out_err->stderr[1]);
	if (ft_put_file_in_str(std_out_err->stdout[0], &res->output) != 0)
		return (ft_free_output_co(&res, &std_out_err));
	if (ft_put_file_in_str(std_out_err->stderr[0], &res->error) != 0)
		return (ft_free_output_co(&res, &std_out_err));
	if (!res->output && !res->error)
		res->output = ft_strdup("");
	waitpid(pid, 0, 0);
	close(std_out_err->stdout[0]);
	close(std_out_err->stderr[0]);
	free(std_out_err);
	return (res);
}
