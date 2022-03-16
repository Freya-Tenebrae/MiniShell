/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:45:06 by gadeneux          #+#    #+#             */
/*   Updated: 2022/03/16 14:19:37 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static char	*ft_tools_read_fd(int fd)
{
	char	*buf;
	char	*res;
	int		ret;

	ret = 0;
	res = ft_strdup("");
	if (!res || res == NULL)
		return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	buf = NULL;
	while ((ret = get_next_line(fd, &buf)))
	{
		ft_str_writeon(&res, buf);
		free(buf);
		buf = NULL;
		if (!res || res == NULL)
			return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
		ft_char_writeon(&res, '\n');
		if (!res || res == NULL)
			return (ft_put_error_null(GENERIC_ERROR, "malloc error"));
	}
	free(buf);
	buf = NULL;
	return (res);
}

static int	ft_redirection_read_file(t_elem *list)
{
	int	in_fd;

	if (list->type == IN)
	{
		if (ft_check_one_access_ok_mute(list) != 0)
			return (-1);
		in_fd = ft_redirection_get_fd_in(list);
		if (in_fd < 2)
			return (0);
		list->in_content = ft_tools_read_fd(in_fd);
		close(in_fd);
	}
	return (1);
}

static int	ft_redirection_fill_in(t_data **data, t_elem *cmd)
{
	t_elem	*cursor;

	cursor = cmd;
	while (cursor && cursor->type != PIPE)
	{
		ft_redirection_read_heredoc(data, cursor);
		cursor = cursor->next;
	}
	cursor = cmd;
	while (cursor && cursor->type != PIPE)
	{
		ft_redirection_read_file(cursor);
		cursor = cursor->next;
	}
	return (1);
}

static int	ft_redirection_open_in(t_data **data, t_elem *list)
{
	while (list)
	{
		ft_redirection_fill_in(data, list);
		list = ft_elem_get_right(list);
	}
	return (0);
}

int	ft_redirection_open_out(t_elem *list)
{
	t_elem	*left;
	int		out_fd;

	left = 0;
	while (list)
	{
		left = ft_elem_clone_left(list);
		if (!left)
			return (0);
		if (ft_redirection_out_present(list))
		{
			out_fd = ft_redirection_get_fd_out(list);
			if (out_fd > 2)
				list->out_fd = out_fd;
		}
		list = ft_elem_get_right(list);
		ft_free_elem(&left);
	}
	return (1);
}

int	ft_redirection_open_all(t_data **data, t_elem *list)
{
	ft_redirection_open_out(list);
	ft_redirection_open_in(data, list);
	return (1);
}

char	*ft_get_filename_in(t_elem *list)
{
	char	*result;

	result = NULL;
	while (list)
	{
		if (list->type == PIPE)
			break ;
		if (list->type == IN)
			result = list->next->str;
		list = list->next;
	}
	return (result);
}

char	*ft_redirection_get_in(t_elem *cmd)
{
	char	*result;

	result = NULL;
	while (cmd)
	{
		if (cmd->type == PIPE)
			break ;
		if (cmd->in_content && cmd->in_content != NULL)
			result = cmd->in_content;
		cmd = cmd->next;
	}
	return (result);
}

char	*ft_redirection_get_heredoc(t_elem *cmd)
{
	char	*result;

	result = NULL;
	while (cmd)
	{
		if (cmd->type == PIPE)
			break ;
		if (cmd->type == DOUBLE_IN)
			result = cmd->next->str;
		cmd = cmd->next;
	}
	return (result);
}
