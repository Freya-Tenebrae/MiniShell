/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_expension_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:41:39 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 14:05:40 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_exp_inject3(char *tmp, int i, char **result)
{
	if (tmp)
		free(tmp);
	if (i == 0)
	{
		ft_char_writeon(result, '$');
		if (!*result)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	return (i);
}

static int	ft_exp_inject2(t_data **data, char *str, char **result)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		ft_char_writeon(&tmp, str[i]);
		if (!tmp)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		i++;
	}
	if (ft_getenv(data, tmp) && ft_getenv(data, tmp)->value)
	{
		ft_str_writeon(result, ft_getenv(data, tmp)->value);
		if (!*result)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	return (ft_exp_inject3(tmp, i, result));
}

int	ft_expension_inject(t_data **data, char *str, char **result)
{
	char	*buff;

	if (str[0] && str[0] == '?')
	{
		buff = ft_itoa(g_status_minishell.status_pipe);
		if (!buff)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		ft_str_writeon(result, buff);
		free(buff);
		if (!*result)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		return (1);
	}
	return (ft_exp_inject2(data, str, result));
}
