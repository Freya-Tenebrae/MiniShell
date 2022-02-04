/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:18:49 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/04 16:32:14 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_exec_line(t_data **data, t_elem *list)
{
	t_elem	*listptr;
	char	*infile;

	infile = NULL;
	listptr = list;
	while (listptr && listptr != NULL)
		listptr = ft_run_cmd(data, listptr, &infile);
	if (infile != NULL)
		free(infile);
}

static int	ft_pars_line(t_data **data, char **str, int *ret, \
																t_elem **list)
{
	if (!ft_check_quote(*str))
		return (ft_put_error(GENERIC_ERROR, "Quote error"));
	ft_replace_env(data, str);
	*ret = 0;
	*list = ft_read_command(*str, ret);
	if (*list == NULL || *ret != READ_OK)
		return (1);
	return (0);
}

int	ft_run_line(char **str, t_data **data)
{
	int		ret;
	int		res_pars_line;
	t_elem	*list;

	if (ft_strcmp("exit", *str) == 0)
		return (-1);
	res_pars_line = ft_pars_line(data, str, &ret, &list);
	if (res_pars_line == 0)
	{
		if (ft_check_syntaxe_operator(list) == 0)
			ft_exec_line(data, list);
		ft_free_elem(&list);
	}
	return (0);
}
