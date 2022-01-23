/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2022/01/23 02:09:58 by cmaginot         ###   ########.fr       */
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
/*                                  TYPEDEF                                   */
/* ************************************************************************** */
typedef struct s_elem {
	struct s_elem	*next;
	int				type;
	char			*str;
}					t_elem;

typedef struct s_output {
	char			*output;
	char			*error;
}					t_output;

typedef struct s_env {
	char			*value;
	char			*name;
}					t_env;

typedef struct s_data {
	char			**envp;
	char			*path;
	t_env			**env;
}					t_data;

/* ************************************************************************** */
/*                                   GLOBAL                                   */
/* ************************************************************************** */
t_data		*g_minishell;

/* ************************************************************************** */
/*                                  FONCTION                                  */
/* ************************************************************************** */
int			main(int ac, char **av, char **envp);
int			ft_run_line(char **str);
int			ft_tools_command_exist(char *cmd);
int			ft_execute_cmd(char *path, char **cmd_args);
int			ft_isquote(char c);
int			ft_check_quote(char *str);
int			ft_get_operator_type(char *str);
int			ft_char_isoperator(char c);
int			ft_str_isoperator(char *str);
int			ft_str_indexof(char *str, char c);
int			ft_str_lastindexof(char *str, int from, char c);
int			ft_str_iswhitespace(char c);
int			ft_tools_elem_add(t_elem **list, char *str);
int			ft_tools_is_build_in(char *cmd);
void		ft_replace_env(char **str);
void		ft_signal_handler(int signal);
void		ft_init_signal_handling(void);
void		ft_put_prompt(void);
void		ft_freestrs(char ***strs);
void		ft_tools_free_elem(t_elem **elem);
void		ft_tools_free_output(t_output **output);
void		ft_tools_free_env(t_env **env);
void		ft_tools_free_data(t_data **data);
char		*ft_keepinside_quote(char *str);
char		*ft_str_before(char *str, char c);
char		*ft_str_after(char *str, char c);
char		*ft_str_substring(char *str, int begin, int end);
char		*ft_str_writeon(char **str, char *to_add);
char		*ft_char_writeon(char **str, char c);
char		*ft_char_tostring(char c);
char		*ft_tools_get_in(char *path);
char		*ft_tools_get_double_in(char *word);
char		**ft_str_clonetab(char **strs);
t_elem		*ft_tools_put_cmd_not_found(char *cmd);
t_elem		*ft_read_command(char *str, int *ret);
t_elem		*ft_run_cmd(t_elem *elem, char **infile);
t_elem		*ft_run_pipe(t_elem *list, char **infile);
t_elem		*ft_tools_push_out(t_elem *list, char **infile);
t_elem		*ft_tools_push_double_out(t_elem *list, char **infile);
t_elem		*ft_tools_elem_create(char *str);
t_elem		*ft_tools_elem_last(t_elem *list);
t_env		*ft_getenv(char *str);
t_env		**ft_init_env(char **envp);
t_output	*ft_run_bi(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_cd(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_echo(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_env(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_export(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_pwd(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_unset(char *path, char **cmd_args, char *infile);
t_output	*ft_exec_cmd(char *path, char **cmd_args, char *infile);

/* ************************************************************************** */
/*                                   TOOLS                                    */
/* ************************************************************************** */
/* ************************************************************************** */
/*                                    END                                     */
/* ************************************************************************** */
#endif
