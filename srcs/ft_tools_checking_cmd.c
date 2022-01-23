/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_checking_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:35:05 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/23 20:59:05 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_tools_put_error(int i, char *cmd)
{
	if (i == 0)
	{
		ft_putstr("Erreur de syntaxe près du symbole inattendu « ");
		ft_putstr(cmd);
		ft_putstr(" »\n");
	}
	else if (i == 1)
	{
		ft_putstr(cmd);
		ft_putstr(" : commande introuvable\n");
	}
	else if (i == 2)
		ft_putstr("Error Parsing\n");
	return (-1);
}

// call ft_tools_put_cmd_not_found(cdm), and return -1 if command didnt exist
static int ft_tools_check_if_command_exist(char *cmd)
{
	(void)cmd;
	ft_tools_put_error(1, cmd);
	// ^^ UP TO DELETE ^^ //
	// TODO //
	// TODO //
	// TODO //
	// TODO //
	// TODO //
	// TODO //
	return (0);
}

// check if command exist (return 1 if not)
int	ft_tools_check_if_all_commands_exists(t_elem *list)
{
	t_elem *list_ptr;

	list_ptr = NULL;
	while(list != NULL)
	{
		if (list_ptr == NULL)
		{
			if (list->type == PIPE || list->type == DOUBLE_PIPE \
				|| list->type == AND || list->type == DOUBLE_AND)
				return (ft_tools_put_error(0, list->str));
			else if (list->type == ARGUMENT)
			{
				if (ft_tools_check_if_command_exist(list->str) != 0)
					return (-1);
			}
		}
		else
		{
			if (list->type <= 0)
				return (ft_tools_put_error(2, ""));
			else if (list->type == ARGUMENT && list_ptr->type != ARGUMENT)
				if (ft_tools_check_if_command_exist(list->str) != 0)
					return (-1);
			// else if (error of list->type | || > >> < << & && with list_ptr->type)
			// return (ft_tools_put_error(0, list->str));
		}
		list_ptr = list;
		list = list->next;
	}
	return (0);
}
