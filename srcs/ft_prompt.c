/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 15:29:08 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/22 16:06:33 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

void	ft_put_prompt(int i)
{
	if (i == 0)
		ft_putstr("==");
	else if (i < 0)
		ft_putstr("<");
	else if (i > 0)
		ft_putstr(">");
	ft_putstr("minishell~ ");
}
