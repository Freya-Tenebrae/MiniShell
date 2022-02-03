/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:36:11 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/03 17:38:00 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_tools_put_error(int i, char *str)
{
	if (i == GENERIC_ERROR)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (i == ERREUR_OPERATOR)
	{
		ft_putstr_fd("minishell : erreur de syntaxe près du ", STDERR_FILENO);
		ft_putstr_fd("symbole inattendu « ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" »\n", STDERR_FILENO);
	}
	else if (i == ERREUR_CMD_NOT_FOUND)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" : commande introuvable\n", STDERR_FILENO);
	}
	return (-1);
}
