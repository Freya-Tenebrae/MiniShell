/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:45:06 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/28 16:22:11 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static char*	ft_tools_read_fd(int fd)
{
	char	*buf;
	char	*res;
	int		ret;
	
	ret = 0;
	res = 0;
	while ((ret = get_next_line(fd, &buf)))
	{
		ft_str_writeon(&res, buf);
		ft_char_writeon(&res, '\n');
	}
	return (res);
}

static int		ft_redirection_read_heredoc(t_elem *list)
{
	char	*buffer;

	buffer = 0;
	if (list->type == DOUBLE_IN)
	{
		while (1)
		{
			buffer = readline("> ");
			if (ft_str_equal(buffer, list->next->str))
				break ;
			ft_str_writeon(&(list->in_content), buffer);
			ft_str_writeon(&(list->in_content), "\n");
		}
	}
	return (1);
}

static int		ft_redirection_read_file(t_elem *list)
{
	if (list->type == IN)
	{
		int in_fd = ft_redirection_get_fd_in(list);
		if (in_fd < 2)
			return (0);
		list->in_content = ft_tools_read_fd(in_fd);
		close(in_fd);
	}
	return (1);
}

static int		ft_redirection_fill_in(t_elem *cmd)
{
	t_elem	*cursor;

	cursor = cmd;
	while (cursor && cursor->type != PIPE)
	{
		ft_redirection_read_heredoc(cursor);
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

static int		ft_redirection_open_in(t_elem *list)
{
	while (list)
	{
		ft_redirection_fill_in(list);
		list = ft_elem_get_right(list);
	}
	return (0);
}

int		ft_redirection_open_out(t_elem *list)
{
	t_elem	*left;

	left = 0;
	while (list)
	{
		left = ft_elem_clone_left(list);
		if (!left)
			return (0);
		if (ft_redirection_out_present(list))
		{
			int out_fd = ft_redirection_get_fd_out(list);
			if (out_fd < 2)
				return (0);
			list->out_fd = out_fd;
		}
		list = ft_elem_get_right(list);
	}
	return (1);
}

int		ft_redirection_open_all(t_elem *list)
{
	ft_redirection_open_out(list);
	ft_redirection_open_in(list);
	return (1);
}

// Getters

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
