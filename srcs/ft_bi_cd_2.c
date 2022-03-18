/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bi_cd_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:39:29 by cmaginot          #+#    #+#             */
/*   Updated: 2022/03/18 15:44:46 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_move2(t_data **data, char *destination, char **pwd_value)
{
	if (access(destination, F_OK) != 0)
	{
		ft_put_error(CD_ERROR, "destination error : no such file or folder");
		return (1);
	}
	if (ft_getenv(data, "PWD"))
	{
		*pwd_value = ft_getenv(data, "PWD")->value;
		if (*pwd_value != NULL)
			*pwd_value = ft_strdup(*pwd_value);
		if (ft_create_or_update_variable(data, "OLDPWD", *pwd_value) == -1)
		{
			ft_put_error(GENERIC_ERROR, "malloc error");
			return (2);
		}
	}
	return (0);
}

int	ft_move(t_data **data, char *destination)
{
	char	*pwd_value;
	char	*pwd;
	int		ret;

	ret = ft_move2(data, destination, &pwd_value);
	if (ret != 0)
		return (ret);
	ret = chdir(destination);
	if (ret == -1)
	{
		ft_put_error(CD_ERROR, strerror(errno));
		return (1);
	}
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (ft_create_or_update_variable(data, "PWD", pwd) == -1)
	{
		ft_put_error(GENERIC_ERROR, "malloc error");
		return (2);
	}
	return (0);
}
