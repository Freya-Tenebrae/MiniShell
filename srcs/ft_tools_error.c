/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:36:11 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/03 18:23:20 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_print_error_next(int i, char *str, int strlen)
{
	if (i == OPERATOR_ERROR)
	{
		write(STDERR_FILENO, "minishell : Syntax error near symbol « ", 39);
		write(STDERR_FILENO, str, strlen);
		write(STDERR_FILENO, " »\n", 3);
	}
	if (i == CMD_NOT_FOUND_ERROR)
	{
		write(STDERR_FILENO, "minishell : ", 12);
		write(STDERR_FILENO, str, strlen);
		write(STDERR_FILENO, ": Command not found\n", 20);
	}
	if (i == FILENAME_TOO_LONG_ERROR)
	{
		write(STDERR_FILENO, "minishell : Filename too long :", 31);
		write(STDERR_FILENO, str, strlen);
		write(STDERR_FILENO, "\n", 1);
	}
}

static void	ft_print_error(int i, char *str, int strlen)
{
	if (i == GENERIC_ERROR)
	{
		write(STDERR_FILENO, "minishell : ", 12);
		write(STDERR_FILENO, str, strlen);
		write(STDERR_FILENO, "\n", 1);
	}
	if (i == FILE_ERROR)
	{
		write(STDERR_FILENO, "minishell : ", 12);
		write(STDERR_FILENO, str, strlen);
		write(STDERR_FILENO, ": No such file or folder\n", 25);
	}
	if (i == ACCESS_ERROR)
	{
		write(STDERR_FILENO, "minishell : ", 12);
		write(STDERR_FILENO, str, strlen);
		write(STDERR_FILENO, ": Permission denied\n", 20);
	}
	ft_print_error_next(i, str, strlen);
}

int	ft_put_error(int i, char *str)
{
	ft_print_error(i, str, ft_strlen(str));
	return (-1);
}

void	*ft_put_error_null(int i, char *str)
{
	ft_print_error(i, str, ft_strlen(str));
	return (NULL);
}
