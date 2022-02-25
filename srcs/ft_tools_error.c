/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:36:11 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/25 05:32:20 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_put_error_next(int i, char *str)
{
	if (i == OPERATOR_ERROR)
	{
		ft_putstr_fd("minishell : Syntax error near symbol « ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(" »\n", STDERR_FILENO);
	}
	if (i == CMD_NOT_FOUND_ERROR)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Command not found\n", STDERR_FILENO);
	}
	if (i == FILENAME_TOO_LONG_ERROR)
	{
		ft_putstr_fd("minishell : Filename too long :", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
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
		ft_putstr_fd(": No such file or folder\n", STDERR_FILENO);
	}
	if (i == ACCESS_ERROR)
	{
		ft_putstr_fd("minishell : ", STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	}
	ft_put_error_next(i, str);
	return (-1);
}
