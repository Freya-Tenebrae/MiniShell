/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_file_to_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/03 15:00:51 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

static void	ft_tools_free_str_if_empty(char **str)
{
	if (ft_strcmp(*str, "") == 0)
	{
		free(*str);
		*str = NULL;
	}
}

static int	ft_tools_fill_str_by_one_line(int i, char **line, char **str)
{
	if (i != -1)
	{
		ft_str_writeon(str, *line);
		if (*str == NULL)
			return (-1);
		if (i == 1)
		{
			ft_char_writeon(str, '\n');
			if (*str == NULL)
				return (-1);
		}
		free(*line);
	}
	return (0);
}

int	ft_tools_put_file_in_str(int fd, char **str)
{
	char	*line;
	int		i;

	i = 1;
	while (i == 1)
	{
		line = NULL;
		i = get_next_line(fd, &line);
		if (ft_tools_fill_str_by_one_line(i, &line, str) != 0)
			return (-1);
	}
	ft_tools_free_str_if_empty(str);
	return (0);
}

int	ft_tools_put_double_in_str(char *word, char **str)
{
	char	*line;
	int		i;

	i = 1;
	while (i == 1)
	{
		line = NULL;
		i = get_next_line(0, &line);
		if (i != -1 && ft_strcmp(word, line) == 0)
		{
			free(line);
			return (0);
		}
		if (ft_tools_fill_str_by_one_line(i, &line, str) != 0)
			return (-1);
	}
	ft_tools_free_str_if_empty(str);
	return (0);
}
