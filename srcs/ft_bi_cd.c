/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:29 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/18 15:43:25 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	check_valid_home(t_data **data)
{
	t_env	*home;

	home = ft_getenv(data, "HOME");
	return (home && home->value && ft_strlen(home->value) > 0);
}

static int	step6_create_path(char *directory_operand, t_env *pwd_env, \
																char **new_path)
{
	if (ft_str_writeon(new_path, pwd_env->value) == NULL)
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	if (ft_str_writeon(new_path, "/") == NULL)
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	if (ft_str_writeon(new_path, directory_operand) == NULL)
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	return (0);
}

static int	step6(t_data **data, char *directory_operand)
{
	char	*new_path;
	int		res_move;
	t_env	*pwd_env;

	new_path = 0;
	pwd_env = ft_getenv(data, "PWD");
	if (!pwd_env || pwd_env == NULL)
	{
		ft_put_error(CD_ERROR, "PWD not set");
		return (2);
	}
	if (step6_create_path(directory_operand, pwd_env, &new_path) != 0)
		return (2);
	res_move = ft_move(data, new_path);
	free(new_path);
	return (res_move);
}

int	ft_run_bi_cd(t_data **data, char **cmd_args)
{
	char	*directory_operand;
	int		res_move;

	if (!cmd_args || !*cmd_args)
		return (2);
	if (!cmd_args[1])
	{
		if (!check_valid_home(data))
		{
			ft_put_error(GENERIC_ERROR, "cd : HOME not set");
			return (1);
		}
		directory_operand = ft_getenv(data, "HOME")->value;
	}
	else
	{
		directory_operand = cmd_args[1];
		if (cmd_args[2])
			ft_put_error(GENERIC_ERROR, "cd : too much arguments");
	}
	if (directory_operand[0] && directory_operand[0] == '/')
		res_move = ft_move(data, directory_operand);
	else
		res_move = step6(data, directory_operand);
	return (res_move);
}
