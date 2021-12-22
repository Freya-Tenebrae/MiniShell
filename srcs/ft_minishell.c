/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/22 18:06:08 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*pwd;
	int		res_gnl;

	(void) ac;
	(void) av;
	(void) envp;
	g_minishell_status = 0;
	ft_init_signal_handling();
	while (42 == 42)
	{
		pwd = NULL;
		pwd = getcwd(pwd, 0);
		ft_putstr("minishell~ ");
		ft_putstr(pwd);
		free(pwd);
		ft_putstr(" > ");
		res_gnl = get_next_line(0, &str);
		if (res_gnl == 0)
		{
			free(str);
			return (1);
		}
		else if (res_gnl == -1)
			return (-1);
		if (g_minishell_status == 0)
		{
			if (ft_strcmp("exit", str) == 0
			|| ft_strcmp("\\q", str) == 0)
			{
				free(str);
				return (1);
			}
			int ret = 0;
			t_elem *list = ft_readcmd(str, &ret);
			if (ret == READ_OK)
			{
				t_elem *cursor = list;
				
				while (cursor)
				{
					printf("%-3d ~ %s ~\n", cursor->type, cursor->str);
					cursor = cursor->next;
				}
				
				// cursor = list;
				// char *infile = 0;
				// while ((cursor = ft_runcmd_next(cursor, envp, &infile)))
				// 	;
				// free(infile);
				
			} else if (ret == READ_QUOTE_ERR) {
				printf("quote error.\n");
			} else {
				printf("error.\n");
			}
			free(str);
		}
		else if (g_minishell_status == 2)
		{
			return (1);
		}
		else
		{
			g_minishell_status = 0;
		}
	}
	return (0);
}
