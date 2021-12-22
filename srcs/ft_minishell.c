/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/22 16:18:34 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_act(char **str, char **envp)
{
	int ret;
	t_elem *list;
	char *infile;

	if (ft_strcmp("exit", *str) == 0)
	{
		free(*str);
		return (1);
	}
	ret = 0;
	list = ft_readcmd(*str, &ret);
	if (ret == READ_OK)
	{
		infile = NULL;
		while (list)
			list = ft_runcmd_next(list, envp, &infile);
		free(infile);
	}
	else if (ret == READ_QUOTE_ERR) 
		printf("quote error.\n");
	else
	{
		printf("error.\n");
		return (1);
	}
	free(*str);
	return (0);
}

static void	ft_loop(char **envp)
{
	int		res_gnl;
	char	*str;

	while (42 == 42)
	{
		ft_put_prompt(0);
		res_gnl = get_next_line(0, &str);
		if (res_gnl <= 0)
		{
			if (res_gnl == 0)
				free(str);
			break;
		}
		if (g_minishell_status == 0)
		{
			if (ft_act(&str, envp) != 0)
				break;
		}
		else
			g_minishell_status = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	g_minishell_status = 0;
	ft_init_signal_handling();
	ft_loop(envp);
	return (0);
}

// int		main(int ac, char **av, char **envp)
// {
// 	(void) envp;
// 	(void) ac;
// 	(void) av;
	
// 	// echo test|cat -e
// 	// 0123456789ABCDEF
	
// 	int ret = 0;
// 	// t_elem *list = ft_readcmd("echo \" \"|cat", &ret);
// 	// t_elem *list = ft_readcmd("echo \" \"| cat -e", &ret);
// 	// t_elem *list = ft_readcmd("echo test|cat -e", &ret);
// 	// t_elem *list = ft_readcmd("echo \"test|cat -e\" | cat -e", &ret);
// 	t_elem *list = ft_readcmd("echo '|'", &ret);
// 	// t_elem *list = ft_readcmd("echo |", &ret);
// 	if (ret == READ_OK)
// 	{
// 		t_elem *cursor = list;
		
// 		while (cursor)
// 		{
// 			printf("%-3d ~%s~\n", cursor->type, cursor->str);
// 			cursor = cursor->next;
// 		}
// 	} else if (ret == READ_QUOTE_ERR) {
// 		printf("quote error.\n");
// 	} else {
// 		printf("error.\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int	main(int ac, char **av, char **envp)
// {
// 	char	*str;
// 	char	*pwd;
// 	int		res_gnl;

// 	(void) ac;
// 	(void) av;
// 	(void) envp;
// 	g_minishell_status = 0;
// 	ft_init_signal_handling();
// 	while (42 == 42)
// 	{
// 		pwd = NULL;
// 		pwd = getcwd(pwd, 0);
// 		ft_putstr("minishell~ ");
// 		ft_putstr(pwd);
// 		free(pwd);
// 		ft_putstr(" > ");
// 		res_gnl = get_next_line(0, &str);
// 		if (res_gnl == 0)
// 		{
// 			free(str);
// 			return (1);
// 		}
// 		else if (res_gnl == -1)
// 			return (-1);
// 		if (g_minishell_status == 0)
// 		{
// 			if (ft_strcmp("exit", str) == 0
// 			|| ft_strcmp("\\q", str) == 0)
// 			{
// 				free(str);
// 				return (1);
// 			}
// 			int ret = 0;
// 			t_elem *list = ft_readcmd(str, &ret);
// 			if (ret == READ_OK)
// 			{
// 				t_elem *cursor = list;
				
// 				while (cursor)
// 				{
// 					printf("%-3d ~%s~\n", cursor->type, cursor->str);
// 					cursor = cursor->next;
// 				}
				
// 				cursor = list;
// 				char *infile = 0;
// 				while ((cursor = ft_runcmd_next(cursor, envp, &infile)))
// 					;
// 				free(infile);
				
// 			} else if (ret == READ_QUOTE_ERR) {
// 				printf("quote error.\n");
// 			} else {
// 				printf("error.\n");
// 				return (1);
// 			}
// 			free(str);
// 		}
// 		else if (g_minishell_status == 2)
// 		{
// 			return (1);
// 		}
// 		else
// 		{
// 			g_minishell_status = 0;
// 		}
// 	}
// 	return (0);
// }
