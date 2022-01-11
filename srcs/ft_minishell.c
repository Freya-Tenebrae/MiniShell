/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/11 17:03:13 by gadeneux         ###   ########.fr       */
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
	
	//Verifier que les quotes et backslash sont bien fermés sur la ligne de commande.
	if (!ft_check_q(*str))
	{
		printf("Quote error.\n");
		return (1);
	}
	
	// Remplacer les variables d'environnement sur la ligne de commande.
	ft_replace_env(str);
	
	ret = 0;
	list = ft_readcmd(*str, &ret);
	if (ret == READ_OK)
	{
		(void) infile;
		(void) envp;
		while (list)
		{
			printf("%-3d ~%s~\n", list->type, list->str);
			list = list->next;
		}
		infile = NULL;
		while (list)
			list = ft_runcmd_next(list, envp, &infile);
		free(infile);
	} else
	{
		printf("Error.\n");
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
		ft_put_prompt();
		res_gnl = get_next_line(0, &str);
		if (res_gnl <= 0)
		{
			if (res_gnl == 0)
				free(str);
			break;
		}
		if (ft_act(&str, envp) != 0)
			break;
	}
}

static int	ft_init_minishell_global(char **envp)
{
	minishell = malloc(sizeof(t_data));
	if (!minishell)
		return (0);	
	minishell->envp = envp;
	minishell->path = ft_getpath(envp);
	minishell->env = ft_init_env(envp);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	
	ft_init_minishell_global(envp);
	ft_init_signal_handling();
	ft_loop(envp);
	return (0);
}
