/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/22 18:15:48 by gadeneux         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	ft_init_signal_handling();
	ft_loop(envp);
	return (0);
}
