/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_v2_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:45:06 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/27 17:07:04 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static char*	ft_read_fd(int fd)
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

int		ft_open_redirections(t_elem *list)
{
	ft_open_in(list);
	ft_open_double_in(list);
	return (1);
}

int		ft_open_double_in(t_elem *list)
{
	char	*buffer;
	t_elem	*left;

	left = 0;
	while (list)
	{
		left = ft_elem_clone_left(list);
		if (!left)
			return (0);
		if (ft_redirection_double_in_present(left))
		{
			while (1)
			{
				buffer = readline("> ");
				if (ft_str_equal(buffer, ft_get_fd_redirection_double_in(list)))
					break ;
				ft_str_writeon(&(list->in_content), buffer);
				ft_str_writeon(&(list->in_content), "\n");
			}
		}
		list = ft_elem_get_right(list);
	}
	return (1);
}

int		ft_open_in(t_elem *list)
{
	t_elem	*left;

	left = 0;
	while (list)
	{
		left = ft_elem_clone_left(list);
		if (!left)
			return (0);
		if (ft_redirection_in_present(list))
		{
			int in_fd = ft_get_fd_redirection_in(list);
			if (in_fd < 2)
				return (0);
			list->in_content = ft_read_fd(in_fd);
			close(in_fd);
		}
		list = ft_elem_get_right(list);
	}
	return (1);
}