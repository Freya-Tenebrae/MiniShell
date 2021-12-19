/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/19 01:34:10 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

// int		main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;
// 	(void) envp;
	
// 	// t_elem *list = ft_readcmd("ls -la | grep git | wc -l");
// 	// t_elem *cursor = list;
// 	// char *infile = 0;
// 	// while ((cursor = ft_runcmd_next(cursor, envp, &infile)))
// 	// 	;
// 	// free(infile);
// 	// char *str = 0;
// 	// ft_writechar_on(&str, 'a');
// 	// ft_writechar_on(&str, 'b');
// 	// ft_writechar_on(&str, 'c');
// 	// printf("%s\n", str);
// 	// char *str = ft_runcmd(ft_getpath(envp), "ls -la", 0);
// 	// printf("Output: \n");
// 	// printf("\"%s\"\n", str);
// 	// str = ft_runcmd(ft_getpath(envp), "grep srcs", str);
// 	// printf("Output: \n");
// 	// printf("\"%s\"\n", str);
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*pwd;
	int		res_gnl;

	(void) ac;
	(void) av;
	while (42 == 42)
	{
		pwd = NULL;
		pwd = getcwd(pwd, 0);
		ft_putstr("minishell~ ");
		ft_putstr(pwd);
		free(pwd);
		ft_putstr(" > ");
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
		t_elem *list = ft_readcmd(str);
		if (!list)
			return (1);
		t_elem *cursor = list;
		char *infile = 0;
		while ((cursor = ft_runcmd_next(cursor, envp, &infile)))
			;
		free(infile);
		free(str);
	}
	return (0);
}
