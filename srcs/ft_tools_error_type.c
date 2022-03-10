/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_error_type.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:36:11 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/10 10:37:20 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_put_error(int i, char *str)
{
	ft_print_error(i, str);
	return (-1);
}

void	*ft_put_error_null(int i, char *str)
{
	ft_print_error(i, str);
	return (NULL);
}

void	ft_put_error_void(int i, char *str)
{
	ft_print_error(i, str);
	return ;
}
