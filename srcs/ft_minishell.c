/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/18 21:30:26 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int		main(void)
{
	ft_isoperator(0);
	t_elem *list = ft_readcmd("   input < cat -e test.sh | | grep script.sh > output");
	if (!list)
	{
		printf("Error\n");
		return (0);
	}
	while (list)
	{
		printf("%-10s [%d]\n", list->str, list->type);
		list = list->next;
	}
	return (0);
}
// int	main()
// {
// 	char	*str;
// 	char	*pwd;
// 	int		res_gnl;

// 	while (42 == 42)
// 	{
// 		pwd = NULL;
// 		pwd = getcwd(pwd, 0);
// 		ft_putstr("minishell~ ");
// 		ft_putstr(pwd);
// 		free(pwd);
// 		ft_putstr(" >");
// 		res_gnl = get_next_line(0, &str);
// 		if (res_gnl == -1)
// 			return (-1);
// 		if (ft_strcmp("exit", str) == 0)
// 		{
// 			free(str);
// 			return (1);
// 		}
// 		ft_putstr(str);
// 		ft_putstr("\n");
// 		free(str);
// 	}
// 	return (0);
// }