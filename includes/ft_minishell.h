/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2021/12/22 18:06:23 by gadeneux         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>


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
# define DOUBLE_PIPE 7
# define AND 8
# define DOUBLE_AND 9

# define READ_OK 0
# define READ_ERR -1
# define READ_ALLOC_ERR -2
# define READ_QUOTE_ERR -3

/* ************************************************************************** */
/*                                 VAR GLOBAL                                 */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                  TYPEDEF                                   */
/* ************************************************************************** */
typedef struct	s_elem {
	struct s_elem	*next;
	int				type;
	char			*str;
}				t_elem;

typedef struct s_output {
	char *output;
	char *error;
}				t_output;

/* ************************************************************************** */
/*                                  FONCTION                                  */
/* ************************************************************************** */
int		main(int ac, char **av, char **envp);
t_elem	*ft_readcmd(char *str, int *ret);
int		ft_execcmd(char *path, char **cmd_args);
char	*ft_getpath(char **envp);
t_output	*ft_runcmd(char *path, char **cmd_args, char *infile);
t_elem	*ft_runcmd_next(t_elem *elem, char **envp, char **infile);
/* ************************************************************************** */
/*                                   TOOLS                                    */
/* ************************************************************************** */
int		ft_str_isoperator(char *str);
int		ft_char_isoperator(char c);
char	*ft_writestr_on(char **str, char *to_add);
char	*ft_writechar_on(char **str, char c);
char	*ft_chartostring(char c);
char	*ft_keepinside_q(char *str);
void	ft_signal_handler(int signal);
void	ft_init_signal_handling();
void	ft_put_prompt();
/* ************************************************************************** */
/*                                    END                                     */
/* ************************************************************************** */
#endif
