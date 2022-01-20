/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/20 17:24:45 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

t_elem	*ft_run_cmd_next_line(t_elem *list, char **infile)
{
	if (list->type == ARGUMENT)
		return (ft_runcmd_next(list, infile));
	if (list->type == OUT)
		ft_tools_push_out(list, infile);
	if (list->type == DOUBLE_OUT)
		ft_tools_push_double_out(list, infile);
	// if (list->type == PIPE)
	// 	;
	// if (list->type == DOUBLE_PIPE)
	// 	;
	// if (list->type == AND)
	// 	;
	// if (list->type == DOUBLE_AND)
	// 	;
	return (NULL);
}

static int	ft_act(char **str)
{
	int ret;
	t_elem *list;
	t_elem *listptr;
	char *infile;

	if (ft_strcmp("exit", *str) == 0)
	{
		free(*str);
		return (1);
	}
	
	//Verifier que les quotes et backslash sont bien fermés sur la ligne de commande.
	if (!ft_check_quote(*str))
	{
		printf("Quote error.\n");
		return (1);
	}
	
	// Remplacer les variables d'environnement sur la ligne de commande.
	ft_replace_env(str);

	ret = 0;
	list = ft_read_command(*str, &ret);
	if (ret == READ_OK)
	{
		infile = NULL;
		listptr = list;
		while (listptr && listptr != NULL)
			listptr = ft_run_cmd_next_line(listptr, &infile);
		free(infile);
		// free list
	}
	else
	{
		printf("Error.\n");
		return (1);
	}
	free(*str);
	return (0);
}

static void	ft_loop()
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
		if (ft_act(&str) != 0)
			break;
	}
}

static int	ft_init_minishell_global(char **envp)
{
	minishell = malloc(sizeof(t_data));
	if (!minishell)
		return (0);	
	minishell->envp = envp;
	minishell->env = ft_init_env(envp);
	minishell->path = ft_getenv("PATH")->value;
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	
	ft_init_minishell_global(envp);
	ft_init_signal_handling();
	ft_loop();
	//ft_free_global;
	return (0);
}
