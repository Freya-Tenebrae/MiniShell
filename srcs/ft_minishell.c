/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/20 13:49:25 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

// int		main(int ac, char **av, char **envp)
// {
// 	(void) ac;
// 	(void) av;
// 	(void) envp;
	
// 	char **cmd_args = malloc(sizeof(char*) * 3);
// 	cmd_args[0] = ft_strdup("ls");
// 	cmd_args[1] = ft_strdup("-la");
// 	cmd_args[2] = NULL;
// 	ft_execcmd(ft_getpath(envp), cmd_args);
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	char	*str;
	char	*pwd;
	int		res_gnl;

	(void) ac;
	(void) av;
	(void) envp;
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
		
		t_elem *list = ft_readcmd(str);
		if (!list)
			return (1);
			
		t_elem *cursor = list;
		
		while (cursor)
		{
			printf("%-3d ~%s~\n", cursor->type, cursor->str);
			cursor = cursor->next;
		}
		
		cursor = list;
		char *infile = 0;
		while ((cursor = ft_runcmd_next(cursor, envp, &infile)))
			;
		free(infile);
		free(str);
	}
	return (0);
}
