/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:09:57 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/22 20:43:57 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\b\b  ", 1);
		ft_putstr("\n");
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
		ft_put_prompt();
	}
	else if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}

void	ft_init_signal_handling(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
}