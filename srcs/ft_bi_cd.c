/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:29 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/04 18:25:43 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;

int		check_valid_home(t_data **data)
{
	t_env	*home;

	home = ft_getenv(data, "HOME");
	return (home && home->value && ft_strlen(home->value) > 0);
}

int		is_dot_or_dotdot(char *directory_operand)
{
	char	*first;

	if (ft_str_indexof(directory_operand, '/') != -1)
	{
		first = ft_str_before(directory_operand, '/');
		if (!first)
			return (-1);
		if (ft_strcmp(first, ".") == 0 || ft_strcmp(first, "..") == 0)
		{
			free(first);
			return (1);
		}
	}
	return (ft_strcmp(directory_operand, ".") == 0 || ft_strcmp(directory_operand, "..") == 0);
}

void	ft_move(t_data **data, char *destination)
{
	char	*pwd;
	int		ret;
	
	pwd = 0;
	ret = chdir(destination);
	pwd = getcwd(pwd, 0);
	free(ft_getenv(data, "PWD")->value);
	ft_getenv(data, "PWD")->value = pwd;
}

void	step6(t_data **data, char *directory_operand)
{
	char	*new_path;

	new_path = 0;
	ft_str_writeon(&new_path, ft_getenv(data, "PWD")->value);
	ft_str_writeon(&new_path, "/");
	ft_str_writeon(&new_path, directory_operand);
	ft_move(data, directory_operand);
	free(new_path);
}

void	step7(t_data **data, char *directory_operand)
{
	ft_move(data, directory_operand);
}

void	ft_run_bi_cd(t_data **data, char **cmd_args)
{
	char *directory_operand;

	if (!cmd_args[1])
	{
		if (!check_valid_home(data))
		{
			ft_putstr_fd("minishell: cd: HOME not set", STDERR_FILENO);
			return ;
		}
		directory_operand = ft_getenv(data, "HOME")->value;
	} else {
		directory_operand = cmd_args[1];
	}
	
	if (directory_operand[0] && directory_operand[0] == '/')
		step7(data, directory_operand);
	else if (is_dot_or_dotdot(directory_operand))
		step6(data, directory_operand);
	else
	{
		ft_move(data, directory_operand);
	}
}