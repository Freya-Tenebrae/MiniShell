/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/03 18:04:25 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_loop(t_data **data)
{
	int		res_gnl;
	char	*str;

	while (42 == 42)
	{
		ft_putstr_fd("minishell~ ", STDOUT_FILENO);
		res_gnl = get_next_line(0, &str);
		if (res_gnl <= 0)
		{
			if (res_gnl == 0)
				if (str)
					free(str);
			break ;
		}
		if (ft_run_line(&str, data) != 0)
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

static int	ft_init_minishell_data(t_data **data, char **envp)
{
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (0);
	(*data)->envp = envp;
	(*data)->env = ft_init_env(envp);
	(*data)->path = ft_getenv(data, "PATH")->value;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void) ac;
	(void) av;
	ft_init_minishell_data(&data, envp);
	ft_init_signal_handling();
	ft_loop(&data);
	ft_tools_free_data(&data);
	return (0);
}
