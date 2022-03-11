/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:32 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/11 14:46:59 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_run_bi_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd || pwd == NULL)
	{
		ft_put_error_void(PWD_ERROR, strerror(errno));
		return (2);
	}
	ft_putstr(pwd);
	ft_putchar('\n');
	free(pwd);
	return (0);
}
