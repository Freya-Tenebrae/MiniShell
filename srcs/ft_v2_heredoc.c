/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 17:01:22 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/21 13:20:17 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static int	ft_is_eof(char *buffer, char *eof)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = ft_keepinside_quote(eof);
	if (!tmp)
		ret = -1;
	else if (ft_str_equal(buffer, tmp))
		ret = 1;
	else
		ret = 0;
	if (tmp)
		free(tmp);
	return (ret);
}

static int	test(t_data **data, t_elem *list, int eof_ret, char **buffer)
{
	if (!ft_havequote(list->next->str))
		ft_expension_on_heredoc(data, buffer);
	if (eof_ret == -1)
		return (ft_put_error(GENERIC_ERROR, "malloc error"));
	if (!eof_ret)
	{
		ft_str_writeon(&(list->in_content), *buffer);
		if (list->in_content == NULL)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		ft_str_writeon(&(list->in_content), "\n");
		if (list->in_content == NULL)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
	}
	else
		return (1);
	return (0);
}

static int	ft_redirection_read_heredoc_test_buffer(char *buffer)
{
	if (buffer == NULL)
	{
		if (g_status_minishell.status_heredoc == 1)
			return (0);
		ft_put_error(GENERIC_ERROR, "warning: «here-doc» reach eof");
		return (1);
	}
	return (2);
}

int	ft_redirection_read_heredoc(t_data **data, t_elem *list)
{
	char	*buffer;
	int		ret;

	if (list->type == DOUBLE_IN)
	{
		list->in_content = ft_strdup("");
		if (!list->in_content || list->in_content == NULL)
			return (ft_put_error(GENERIC_ERROR, "malloc error"));
		while (1)
		{
			buffer = readline("> ");
			ret = ft_redirection_read_heredoc_test_buffer(buffer);
			if (ret != 2)
				return (ret);
			ret = ft_is_eof(buffer, list->next->str);
			ret = test(data, list, ret, &buffer);
			if (buffer)
				free(buffer);
			if (ret != 0)
				return (ret);
		}
	}
	return (1);
}
