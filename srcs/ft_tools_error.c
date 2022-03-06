/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 18:36:11 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/06 10:25:38 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_malloc_error_on_error_management(void)
{
	write(STDERR_FILENO, "minishell : malloc error on error management\n", 45);
}

static void	ft_print_error_type(int i, char **error_str)
{
	if (i == GENERIC_ERROR)
		ft_str_writeon(error_str, "\n");
	if (i == FILE_ERROR)
		ft_str_writeon(error_str, " : No such file or folder\n");
	if (i == ACCESS_ERROR)
		ft_str_writeon(error_str, " : Permission denied\n");
	if (i == OPERATOR_ERROR)
		ft_str_writeon(error_str, " »\n");
	if (i == CMD_NOT_FOUND_ERROR)
		ft_str_writeon(error_str, " : Command not found\n");
	if (i == FILENAME_TOO_LONG_ERROR)
		ft_str_writeon(error_str, " : Filename too long\n");
	if (i == NUMERIC_ARG_NEEDED_ERROR)
		ft_str_writeon(error_str, " : numeric argument needed\n");
}

static void	ft_print_error(int i, char *str)
{
	char	*error_str;

	error_str = NULL;
	if (i != OPERATOR_ERROR)
		ft_str_writeon(&error_str, "minishell : ");
	else
		ft_str_writeon(&error_str, "minishell : Syntax error near symbol « ");
	if (!error_str || error_str == NULL)
		return ft_malloc_error_on_error_management();
	ft_str_writeon(&error_str, str);
	if (!error_str || error_str == NULL)
		return ft_malloc_error_on_error_management();
	ft_print_error_type(i, &error_str);
	if (!error_str || error_str == NULL)
		return ft_malloc_error_on_error_management();
	write(STDERR_FILENO, error_str, ft_strlen(error_str));
}

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
