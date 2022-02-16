/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:09:57 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/16 14:08:55 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\b\b  ", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (g_status_minishell <= 0)
			rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
}

void	ft_init_signal_handling(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
}
