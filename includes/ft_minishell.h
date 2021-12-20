/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/20 20:59:15 by gadeneux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft/libft.h"
# include "Get_next_line/get_next_line.h"

/* ************************************************************************** */
/*                                   DEFINE                                   */
/* ************************************************************************** */
# define ARGUMENT 1
# define IN 2
# define DOUBLE_IN 3
# define OUT 4
# define DOUBLE_OUT 5
# define PIPE 6

# define READ_OK 0
# define READ_ERR -1
# define READ_ALLOC_ERR -2
# define READ_QUOTE_ERR -3

/* ************************************************************************** */
/*                                 VAR GLOBAL                                 */
/* ************************************************************************** */
int	g_minishell_status;
# define STATUS_ON 0
# define STATUS_SKIP 1
# define STATUS_EXIT 2

/* ************************************************************************** */
/*                                  TYPEDEF                                   */
/* ************************************************************************** */
typedef struct	s_elem {
	struct s_elem	*next;
	int				type;
	char			*str;
}				t_elem;

/* ************************************************************************** */
/*                                  FONCTION                                  */
/* ************************************************************************** */
int		main(int ac, char **av, char **envp);
t_elem	*ft_readcmd(char *str, int *ret);
int		ft_execcmd(char *path, char **cmd_args);
char	*ft_getpath(char **envp);
char	*ft_runcmd(char *path, char **cmd_args, char *infile, int *ret);
t_elem	*ft_runcmd_next(t_elem *elem, char **envp, char **infile);
/* ************************************************************************** */
/*                                   TOOLS                                    */
/* ************************************************************************** */
int		ft_isoperator(char *str);
char	*ft_writestr_on(char **str, char *to_add);
char	*ft_writechar_on(char **str, char c);
char	*ft_chartostring(char c);
/* ************************************************************************** */
/*                                    END                                     */
/* ************************************************************************** */
#endif
