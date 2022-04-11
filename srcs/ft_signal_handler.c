/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 16:32:20 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/21 13:01:36 by cmaginot         ###   ########.fr       */
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
		if (g_status_minishell.status_minishell <= 0)
			rl_redisplay();
		g_status_minishell.status_pipe = 130;
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

static void	ft_signal_handler_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\b\b  ", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		g_status_minishell.status_heredoc = 1;
		close(STDIN_FILENO);
		g_status_minishell.status_pipe = 130;
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
}

void	ft_init_signal_handling_heredoc(void)
{
	signal(SIGINT, ft_signal_handler_heredoc);
	signal(SIGQUIT, ft_signal_handler_heredoc);
}
