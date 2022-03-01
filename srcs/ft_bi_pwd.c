/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:32 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/01 12:10:20 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;

t_output	*ft_run_bi_pwd(void)
{
	char  *pwd;
	t_output *out;

	pwd = NULL;
	out = malloc(sizeof(t_output));
	if (!out || out == NULL)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (0);
	}
	pwd = getcwd(pwd, 0);
	if (!pwd || pwd == NULL)
	{
		out->output = NULL;
		out->error = ft_strdup("minishell: pwd: null");
		if (!pwd || pwd == NULL)
		{
			free(out);
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (0);
		}
	}
	ft_char_writeon(&pwd, '\n');
	out->error = NULL;
	out->output = pwd;
	return (out);
}
