/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:57 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/09 14:43:42 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_run_bi_env(t_data **data)
{
	int	i;

	i = 0;
	while (((*data)->env)[i])
	{
		if (((*data)->env)[i]->value)
		{
			ft_putstr(((*data)->env)[i]->name);
			ft_putchar('=');
			ft_putstr(((*data)->env)[i]->value);
			ft_putchar('\n');
		}
		i++;
	}
	return (0);
}
