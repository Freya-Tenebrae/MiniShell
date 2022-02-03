/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/03 15:00:44 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_loop(void)
{
	int		res_gnl;
	char	*str;

	while (42 == 42)
	{
		ft_putstr("minishell~ ");// check fd
		res_gnl = get_next_line(0, &str);
		if (res_gnl <= 0)
		{
			if (res_gnl == 0)
				if (str)
					free(str);
			break ;
		}
		if (ft_run_line(&str) != 0)
		{
			if (str)
				free(str);
			break ;
		}
		else
			if (str)
				free(str);
	}
}

static int	ft_init_minishell_global(char **envp)
{
	g_minishell = malloc(sizeof(t_data));
	if (!g_minishell)
		return (0);
	g_minishell->envp = envp;
	g_minishell->env = ft_init_env(envp);
	g_minishell->path = ft_getenv("PATH")->value;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	ft_init_minishell_global(envp);
	ft_init_signal_handling();
	ft_loop();
	ft_tools_free_data(&g_minishell);
	return (0);
}
