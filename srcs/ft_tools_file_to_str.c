/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools_file_to_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 12:28:11 by gadeneux          #+#    #+#             */
/*   Updated: 2022/02/25 18:46:36 by cmaginot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_minishell.h"

// static void	ft_free_str_if_empty(char **str)
// {
// 	if (*str && ft_strcmp(*str, "") == 0)
// 	{
// 		free(*str);
// 		*str = NULL;
// 	}
// }

// static int	ft_fill_str_by_one_line(int i, char **line, char **str)
// {
// 	if (i != -1)
// 	{
// 		ft_str_writeon(str, *line);
// 		if (!*str || *str == NULL)
// 		{
// 			free(*line);
// 			return (ft_put_error(GENERIC_ERROR, "malloc error"));
// 		}
// 		if (i == 1)
// 		{
// 			ft_char_writeon(str, '\n');
// 			if (*str == NULL)
// 			{
// 				free(*line);
// 				return (ft_put_error(GENERIC_ERROR, "malloc error"));
// 			}
// 		}
// 		free(*line);
// 	}
// 	return (0);
// }

// int	ft_put_double_in_str(char *word, char **str)
// {
// 	char	*line;

// 	while (42 == 42)
// 	{
// 		line = readline("> ");
// 		if (line == NULL)
// 			return (ft_put_error(GENERIC_ERROR, "readline error"));
// 		if (ft_strcmp(word, line) == 0)
// 		{
// 			free(line);
// 			return (0);
// 		}
// 		if (ft_fill_str_by_one_line(1, &line, str) != 0)
// 			return (-1);
// 	}
// 	ft_free_str_if_empty(str);
// 	return (0);
// }
