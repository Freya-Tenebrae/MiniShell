/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:36:11 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/03 15:00:49 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_tools_put_error(int i, char *str)
{
	if (i == GENERIC_ERROR)
	{
		ft_putstr_fd("minishell : ", 2);// check fd
		ft_putstr_fd(str, 2);// check fd
		ft_putchar_fd('\n', 2);// check fd
	}
	else if (i == ERREUR_OPERATOR)
	{
		ft_putstr_fd("minishell : erreur de syntaxe près du ", 2);// check fd
		ft_putstr_fd("symbole inattendu « ", 2);// check fd
		ft_putstr_fd(str, 2);// check fd
		ft_putstr_fd(" »\n", 2);// check fd
	}
	else if (i == ERREUR_CMD_NOT_FOUND)
	{
		ft_putstr_fd("minishell : ", 2);// check fd
		ft_putstr_fd(str, 2);// check fd
		ft_putstr_fd(" : commande introuvable\n", 2);// check fd
	}
	return (-1);
}
