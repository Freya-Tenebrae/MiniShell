/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:09:57 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/09 16:43:46 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\b\b  ", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		// rl_replace_line("", 0);
		ft_putstr_fd("minishell~ ", STDOUT_FILENO);
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
