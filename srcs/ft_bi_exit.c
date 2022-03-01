/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 04:43:04 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/01 12:08:19 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

//	pour les output : 
//		si il n'y a pas d'erreur, out->output ne devra ni etre non attribuer 
//			ni nul et out->error devra etre NULL
//		si il y a une erreur elle devra etre mise dans out->error
//			(argument, fonction didn't exist, ...) et out->output devra etre 
//			set a NULL;

t_output	*ft_run_bi_exit(char **cmd_args)
{
	if (g_status_minishell != 2)
	{
		g_status_minishell = -1;
	}
	// g_status_minishell :
	//		-1 = exit
	//		0 = run 
	//		1 : running line witout pipe 
	//		2 running line with pipe
	(void)cmd_args;
	// la version actuelle met un output error ce qui est normal
	return (NULL);
}

//	- exit -> exit normalement
//	- exit "arg numerique" -> exit normalement
//	- exit "arg non numerique"  -> msg argument numerique necessaire puis exit
//	- exit "plusieur arguments" -> erreur non numerique if 1rst non numerique 
//			(mais quitte si un seul arg numerique) sinon msg trop d'arguments
//	- presence d'un pipe (avant ou apres) : n'existe pas mais passe a la 
//			commande suivante 
//	- le mettre en bi specifique ...