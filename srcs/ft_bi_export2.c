/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:37 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/16 17:59:45 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	test1(t_data **data, char **cmd_args, int i)
{
	if (!ft_is_valid_variable_identifier(cmd_args[i]))
	{
		ft_put_error(IDENTIFIER_VAR_ERROR, cmd_args[i]);
		return (-1);
	}
	else if (ft_create_or_update_variable(data, cmd_args[i], \
															NULL) == -1)
		return (-2);
	return (0);
}

static int	test2(t_data **data, char **cmd_args, int i)
{
	char	*tmp;

	tmp = ft_str_before(cmd_args[i], '=');
	if (!tmp)
		return (-1);
	if (!ft_is_valid_variable_identifier(tmp))
	{
		ft_put_error(IDENTIFIER_VAR_ERROR, cmd_args[i]);
		return (0);
	}
	else if (ft_create_or_update_variable(data, tmp, \
								ft_str_after(cmd_args[i], '=')) == -1)
		return (-2);
	free(tmp);
	return (1);
}

static int	ft_fill2(t_data **data, char **cmd_args, int i, int *res)
{
	int		ret;

	ret = 0;
	if (ft_str_indexof(cmd_args[i], '=') == -1)
	{
		ret = test1(data, cmd_args, i) == -2;
		if (ret != 0)
			*res = ret;
		if (ret == -2)
			return (-2);
	}
	else
	{
		ret = test2(data, cmd_args, i);
		if (ret == 0)
			*res = -1;
		if (ret == -1 || ret == -2)
			return (ret);
	}
	return (0);
}

int	ft_fill(char **cmd_args, t_data **data)
{
	int		res;
	int		ret;
	int		i;

	i = 1;
	ret = 0;
	res = 0;
	while (cmd_args[i])
	{
		ret = ft_fill2(data, cmd_args, i, &res);
		if (ret != 0)
			return (ret);
		i++;
	}
	return (res);
}
