/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:29 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/09 17:49:50 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int		ft_move(t_data **data, char *destination)
{
	char	*pwd;
	char	*pwd_value;
	int		ret;
	
	if (ft_getenv(data, "PWD"))
	{
		pwd_value = ft_getenv(data, "PWD")->value;
		if (pwd_value != NULL)
			pwd_value = ft_strdup(pwd_value);
		if (ft_create_or_update_variable(data, "OLDPWD", pwd_value) == -1)
		{
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (2);
		}
	}
	ret = chdir(destination);
	if (ret == -1)
	{
		ft_put_error(CD_ERROR, strerror(errno));
		return (1);
	}
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (ft_create_or_update_variable(data, "PWD", pwd) == -1)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (2);
	}
	return (0);
}

static int		check_valid_home(t_data **data)
{
	t_env	*home;

	home = ft_getenv(data, "HOME");
	return (home && home->value && ft_strlen(home->value) > 0);
}

static int		is_dot_or_dotdot(char *directory_operand)
{
	char	*first;

	if (ft_str_indexof(directory_operand, '/') != -1)
	{
		first = ft_str_before(directory_operand, '/');
		if (!first)
			return (-2);
		if (ft_strcmp(first, ".") == 0 || ft_strcmp(first, "..") == 0)
		{
			free(first);
			return (1);
		}
		free(first);
	}
	return (ft_strcmp(directory_operand, ".") == 0 || ft_strcmp(directory_operand, "..") == 0);
}

static int	step6(t_data **data, char *directory_operand)
{
	char	*new_path;
	int		res_move;

	new_path = 0;
	if (ft_str_writeon(&new_path, ft_getenv(data, "PWD")->value) == NULL)
		return (2);
	if (ft_str_writeon(&new_path, "/") == NULL)
		return (2);
	if (ft_str_writeon(&new_path, directory_operand) == NULL)
		return (2);
	res_move = ft_move(data, directory_operand);
	free(new_path);
	return (res_move);
}

int	ft_run_bi_cd(t_data **data, char **cmd_args)
{
	char	*directory_operand;
	int		res_move;
	int		res_is_dot;

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
	else if (cmd_args[2])
	{
		ft_put_error(GENERIC_ERROR, "cd : too mutch arguments");
		return (1);
	}
	directory_operand = cmd_args[1];
	if (directory_operand[0] && directory_operand[0] == '/')
		res_move = ft_move(data, directory_operand);
	else
	{
		res_is_dot = is_dot_or_dotdot(directory_operand);
		if (res_is_dot == -2)
			return (2);
		else if (res_is_dot)
			res_move = step6(data, directory_operand);
		else
			res_move = ft_move(data, directory_operand);
	}
	return (res_move);
}