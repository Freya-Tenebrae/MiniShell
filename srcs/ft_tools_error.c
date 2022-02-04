/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:36:11 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/04 16:54:21 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_put_error_next(int i, char *str)
{
	if (i == OPERATOR_ERROR)
	{
		ft_putstr_fd("minishell : Erreur de syntaxe près du ", STDERR_FILENO);
		ft_putstr_fd("symbole inattendu « ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" »\n", STDERR_FILENO);
	}
	if (i == CMD_NOT_FOUND_ERROR)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Commande introuvable\n", STDERR_FILENO);
	}
}

int	ft_put_error(int i, char *str)
{
	if (i == GENERIC_ERROR)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (i == FILE_ERROR)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", STDERR_FILENO);
	}
	if (i == ACCESS_ERROR)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission non accordée\n", STDERR_FILENO);
	}
	ft_put_error_next(i, str);
	return (-1);
}
