/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/13 16:07:19 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	main()
{
	char	*str;
	char	*pwd;
	int		res_gnl;

	while (42 == 42)
	{
		pwd = NULL;
		pwd = getcwd(pwd, 0);
		ft_putstr("minishell~ ");
		ft_putstr(pwd);
		free(pwd);
		ft_putstr(" >");
		res_gnl = get_next_line(0, &str);
		if (res_gnl == -1)
			return (-1);
		if (ft_strcmp("exit", str) == 0)
		{
			free(str);
			return (1);
		}
		ft_putstr(str);
		ft_putstr("\n");
		free(str);
	}
	return (0);
}