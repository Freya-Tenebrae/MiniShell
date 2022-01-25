/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:18:49 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/25 03:16:44 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_tools_check_syntaxe_operator(t_elem *list)
{
	t_elem	*list_ptr;

	list_ptr = NULL;
	while (list != NULL)
	{
		if (list->type == PIPE && \
			(list_ptr == NULL || list_ptr->type != ARGUMENT))
			return (ft_tools_put_error(ERREUR_OPERATOR, list->str));
		else if ((list->type == IN || list->type == DOUBLE_IN) && \
			(list_ptr->type != PIPE && list_ptr->type != ARGUMENT))
			return (ft_tools_put_error(ERREUR_OPERATOR, list->str));
		else if ((list->type == OUT || list->type == DOUBLE_OUT) && \
			(list_ptr->type != PIPE && list_ptr->type != ARGUMENT))
			return (ft_tools_put_error(ERREUR_OPERATOR, list->str));
		else if ((list->type == IN || list->type == DOUBLE_IN || \
			list->type == OUT || list->type == DOUBLE_OUT || \
			list->type == PIPE) && list->next == NULL)
			return (ft_tools_put_error(ERREUR_OPERATOR, "/n"));
		list_ptr = list;
		list = list->next;
	}
	return (0);
}

// la fonction va tester si toutes les arguments associes a > >> <
//		sont accesible (R_OK for <) (W_OK for > and >>)
static int	ft_tools_check_access_ok(t_elem *list)
{
	(void)list;
	return (0);
}

static void	ft_exec_line(t_elem *list)
{
	t_elem	*listptr;
	char	*infile;

	infile = NULL;
	listptr = list;
	while (listptr && listptr != NULL)
		listptr = ft_run_cmd(listptr, &infile);
	if (infile != NULL)
		free(infile);
}

static int	ft_pars_line(char **str, int *ret, t_elem **list)
{
	if (!ft_check_quote(*str))
	{
		ft_putstr_fd("Quote error.\n", 2);
		return (1);
	}
	ft_replace_env(str);
	*ret = 0;
	*list = ft_read_command(*str, ret);
	if (*list == NULL || *ret != READ_OK)
		return (1);
	return (0);
}

int	ft_run_line(char **str)
{
	int		ret;
	int		res_pars_line;
	t_elem	*list;

	if (ft_strcmp("exit", *str) == 0)
		return (-1);
	res_pars_line = ft_pars_line(str, &ret, &list);
	if (res_pars_line == 0)
	{
		if (ft_tools_check_syntaxe_operator(list) == 0 && \
			ft_tools_check_access_ok(list) == 0)
			ft_exec_line(list);
		ft_tools_free_elem(&list);
	}
	return (0);
}
