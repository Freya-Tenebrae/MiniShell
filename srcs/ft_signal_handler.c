/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 15:09:57 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/20 16:54:57 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
		rl_on_new_line();
		//rl_replace_line("", 0);
		g_minishell_status = STATUS_SKIP;
	}
	else if (signal == SIGQUIT)
		g_minishell_status = STATUS_ON;
}

void	ft_init_signal_handling(void)
{
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
}