/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:45:07 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/21 15:07:59 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_tools_is_build_in(char *cmd)
{
	(void)cmd;
	return (1);
}

t_output    *ft_run_bi(char *path, char **cmd_args, char *infile)
{
	(void)path;
	(void)cmd_args;
	(void)infile;
	// if (cmd_args[0] == "env")
	// 	return(ft_run_bi_env(cmd_args, infile));
	return (NULL);
}