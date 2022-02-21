/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:29 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/21 15:26:12 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;

void		go_to(char *path)
{
	
}

int		check_valid_home(t_data *data)
{
	t_env	*home;

	home = ft_getenv(data, "HOME");
	return (home && home->value && ft_strlen(home->value) > 0);
}

int		is_dot_or_dotdot(char *directory_operand)
{
	char	*first;

	first = ft_str_before(directory_operand);

}

t_output	*ft_run_bi_cd(char *path, char **cmd_args, char *infile)
{
	t_output *out;
	char *directory_operand;

	(void)path;
	(void)cmd_args;
	(void)infile;
	out = malloc(sizeof(t_output));
	if(!out)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (0);
	}
	if (!cmd_args[1])
	{
		if (!check_valid_home(data))
		{
			out->output = NULL;
			out->error = ft_strdup("minishell: cd: HOME not set");
			if (!out->error)
			{
				ft_put_error(GENERIC_ERROR, "malloc error");
				return (0);
			}
		}
		directory_operand = ft_getenv(data, "HOME")->value;
	} else {
		directory_operand(ft_getenv(data, cmd_args[1]));
	}

	if (directory_operand[0] && directory_operand[0] == '/')
		step7(directory_operand);
	else if (is_dot_or_dotdot(directory_operand))
		step6();

	return (out);
}
