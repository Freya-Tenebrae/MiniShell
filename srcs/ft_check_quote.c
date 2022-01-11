/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 17:30:52 by gadeneux          #+#    #+#             */
/*   Updated: 2022/01/11 16:59:00 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

int		ft_check_q(char *str)
{
	int in_quote = 0;
	char quote = 0;
	int i = 0;

	while (str[i])
	{
		// Si le char est une quote, et que c'est l'ouverture ou une fermeture de quote
		// Si fermeture, vérifie qu'il s'agit de la bonne quote.
		if (ft_isquote(str[i]) && (!quote || quote == str[i]))
		{
			quote = str[i];
			in_quote++;
		}
		// réinitialise la quote à null en cas de fermeture.
		if (in_quote % 2 == 0)
			quote = 0;
		i++;
	}
	if (in_quote && in_quote % 2 != 0)
		return (0);
	return (1);
}