/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/11 14:20:56 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_loop(t_data **data)
{
	char	*str;

	while (42 == 42)
	{
		if (g_status_minishell.status_minishell == -1)
			break ;
		else if (g_status_minishell.status_minishell > 0)
		{
			g_status_minishell.exitcode = 0;
			g_status_minishell.status_minishell = 0;
		}
		str = readline("minishell~ ");
		if (str == NULL)
			break ;
		if (ft_strcmp(str, "") != 0)
		{
			add_history(str);
			ft_run_line(&str, data);
		}
		free(str);
	}
	ft_putstr_fd("exit\n", STDOUT_FILENO);
}

static void	ft_init_minishell_global(void)
{
	g_status_minishell.status_minishell = 0;
	g_status_minishell.status_pipe = 0;
	g_status_minishell.exitcode = 0;
}

static int	ft_init_minishell_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	(*data)->envp = ft_str_clonetab(envp);
	if ((*data)->envp == NULL)
	{
		free(*data);
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	(*data)->env = ft_init_env(envp);
	if (!(*data)->env || (*data)->env == NULL)
	{
		ft_free_data(data);
		return (ft_put_error(GENERIC_ERROR, \
										"environment initialisation error"));
	}
	(*data)->path = ft_getenv(data, "PATH")->value;
	if (!(*data)->path || (*data)->path == NULL)
	{
		ft_free_data(data);
		return (ft_put_error(GENERIC_ERROR, \
										"environment initialisation error"));
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void) ac;
	(void) av;
	ft_init_minishell_global();
	if (ft_init_minishell_data(&data, envp) != 0)
		return (-1);
	ft_init_signal_handling();
	ft_loop(&data);
	ft_free_data(&data);
	return (g_status_minishell.exitcode);
}
