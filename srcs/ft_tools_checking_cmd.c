/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_checking_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:35:05 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/22 18:26:36 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

// check if command exist (return 1 if not)
int	ft_tools_command_exist(char *cmd)
{
	(void)cmd;
	return (0);
}

// put an error message with the name of the cmd, then return error
t_elem	*ft_tools_put_cmd_not_found(char *cmd)
{
	(void)cmd;
	return (NULL);
}
