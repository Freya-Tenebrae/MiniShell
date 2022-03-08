/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:57 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/08 14:18:26 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;

void	ft_run_bi_env(t_data **data)
{
	int	i;

	i = 0;
	while (((*data)->env)[i])
	{
		if (((*data)->env)[i]->value)
		{
			ft_putstr(((*data)->env)[i]->name);
			ft_putchar('=');
			ft_putstr(((*data)->env)[i]->value);
			ft_putchar('\n');
		}
		i++;
	}
}
