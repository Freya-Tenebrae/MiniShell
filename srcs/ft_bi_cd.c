/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:29 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/15 15:31:49 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int	ft_move2(t_data **data, char *destination, char **pwd_value)
{
	if (access(destination, F_OK) != 0)
	{
		ft_put_error(CD_ERROR, "destination error : no such file or folder");
		return (1);
	}
	if (ft_getenv(data, "PWD"))
	{
		*pwd_value = ft_getenv(data, "PWD")->value;
		if (*pwd_value != NULL)
			*pwd_value = ft_strdup(*pwd_value);
		if (ft_create_or_update_variable(data, "OLDPWD", *pwd_value) == -1)
		{
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (2);
		}
	}
	return (0);
}

int	ft_move(t_data **data, char *destination)
{
	char	*pwd_value;
	char	*pwd;
	int		ret;

	ret = ft_move2(data, destination, &pwd_value);
	if (ret != 0)
		return (ret);
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

static int	check_valid_home(t_data **data)
{
	t_env	*home;

	home = ft_getenv(data, "HOME");
	return (home && home->value && ft_strlen(home->value) > 0);
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
