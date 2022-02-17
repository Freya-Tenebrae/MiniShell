/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:57 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/17 17:25:42 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;

t_output	*ft_run_bi_env(t_data **data, char *path, char **cmd_args, \
																char *infile)
{
	t_output	*res;
	int			i;

	(void)path;
	(void)cmd_args;
	(void)infile;

	i = 0;
	res = malloc(sizeof(t_output));
	if (!res)
		return (NULL);
	res->error = 0;
	res->output = ft_strdup("");
	if (!res->output)
		return (NULL);
	while (((*data)->env)[i])
	{
		if (((*data)->env)[i]->value)
		{
				ft_str_writeon(&res->output, ((*data)->env)[i]->name);
			ft_char_writeon(&res->output, '=');
			ft_str_writeon(&res->output, ((*data)->env)[i]->value);
			ft_char_writeon(&res->output, '\n');	
		}
		i++;
	}
	return (res);
}
