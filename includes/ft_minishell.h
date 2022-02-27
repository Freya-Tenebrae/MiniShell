/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:44:43 by cmaginot          #+#    #+#             */
/*   Updated: 2022/02/27 17:01:40 by gadeneux         ###   ########.fr       */
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

# define GENERIC_ERROR 0
# define OPERATOR_ERROR 1
# define CMD_NOT_FOUND_ERROR 2
# define FILE_ERROR 3
# define ACCESS_ERROR 4
# define FILENAME_TOO_LONG_ERROR 5

# define READ_OK 0
# define READ_ERR -1
# define READ_ALLOC_ERR -2
# define READ_QUOTE_ERR -3

# define N_MAC_CHAR_NAME_FILE 144

/* ************************************************************************** */
/*                                  TYPEDEF                                   */
/* ************************************************************************** */
typedef struct s_elem {
	struct s_elem	*next;
	int				type;
	char			*str;
	char			*in_content;
}					t_elem;

typedef struct s_output {
	char			*output;
	char			*error;
}					t_output;

typedef struct s_stdoutanderr {
	int				stdout[2];
	int				stderr[2];
}					t_stdoutanderr;

typedef struct s_env {
	char			*value;
	char			*name;
}					t_env;

typedef struct s_data {
	char			**envp;
	char			*path;
	t_env			**env;
}					t_data;

typedef struct s_redir {
	char			*file;
	int				type;
}					t_redir;

/* ************************************************************************** */
/*                                  GLOBAL                                    */
/* ************************************************************************** */
int			g_status_minishell;
// g_status_minishell == -1 : minishell must exit
// g_status_minishell == 0  : minishell is running
// g_status_minishell == 1  : minishell is executing a line without pipe
// g_status_minishell == 2  : minishell is executing a line with a pipe
// g_status_minishell == 3  : minishell'll force brocking a loop

/* ************************************************************************** */
/*                                  FONCTION                                  */
/* ************************************************************************** */
int			main(int ac, char **av, char **envp);
void		ft_init_signal_handling(void);
void		ft_run_line(char **str, t_data **data);
t_elem		*ft_read_line(char *str, int *ret);
int			ft_read_cmd(char *str, int i, char **buffer, int *is_operator);
int			ft_execute_command(t_data **data, t_elem *list, char **envp);
int			ft_run_execve_with_all_path(char *path, char **cmd_args);

/* ************************************************************************** */
/*                                  BUILD ID                                  */
/* ************************************************************************** */
int			ft_is_build_in(char *cmd);
t_output	*ft_run_bi(t_data **data, char *path, char **cmd_args, \
																char *infile);
t_output	*ft_run_bi_cd(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_echo(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_env(t_data **data, char *path, char **cmd_args, \
																char *infile);
t_output	*ft_run_bi_export(t_data **data, char *path, char **cmd_args, \
																char *infile);
t_output	*ft_run_bi_pwd(char *path, char **cmd_args, char *infile);
t_output	*ft_run_bi_unset(t_data **data, char *path, char **cmd_args, \
																char *infile);
t_output	*ft_run_bi_exit(char *path, char **cmd_args, char *infile);

/* ************************************************************************** */
/*                                   TOOLS                                    */
/* ************************************************************************** */
t_elem		*ft_elem_create(char *str, int is_operator);
t_elem		*ft_elem_last(t_elem *list);
t_elem		*ft_put_args_in_cmd_args(t_elem *list, char ***cmd_args);
int			ft_elem_add(t_elem **list, char *str, int is_operator);
void		ft_free_elem(t_elem **elem);
void		ft_free_output(t_output **output);
t_env		**ft_init_env(char **envp);
t_env		*ft_getenv(t_data **data, char *str);
void		ft_replace_env(t_data **data, char **str);
void		ft_free_env(t_env **env);
void		ft_free_data(t_data **data);

int			ft_redirection_in_present(t_elem *list);
int			ft_redirection_out_present(t_elem *list);
int			ft_get_fd_redirection_in(t_elem *list);
int			ft_get_fd_redirection_out(t_elem *list);
//int			ft_put_double_in_str(char *word, char **str);

int			ft_check_syntaxe_operator(t_elem *list);
int			ft_check_access_ok(t_elem *list);

int			ft_put_error(int i, char *str);

int			ft_isquote(char c);
int			ft_check_quote(char *str);
char		*ft_keepinside_quote(char *str);

int			ft_str_isoperator(char *str);
int			ft_char_isoperator(char c);
int			ft_get_operator_type(char *str);

int			ft_str_indexof(char *str, char c);
int			ft_str_lastindexof(char *str, int from, char c);
int			ft_iswhitespace(char c);
char		*ft_str_before(char *str, char c);
char		*ft_str_after(char *str, char c);
char		*ft_str_writeon(char **str, char *to_add);
char		*ft_char_writeon(char **str, char c);
char		*ft_char_tostring(char c);
char		**ft_str_clonetab(char **strs);
void		ft_freestrs(char ***strs);

int			ft_is_valid_identifier(char *str);
int			ft_str_equal(char *s1, char *s2);
int			ft_env_tab_len(t_env **tab);
t_env		*ft_clone_variable(t_env *env);
t_env		*ft_create_variable(char *name, char *value);
void		ft_free_variable(t_env *env);
int			ft_redirection_double_in_present(t_elem *list);
char		*ft_get_fd_redirection_double_in(t_elem *list);

int			ft_elem_is_redirection(t_elem *elem);
int			ft_elem_get_cmd_args_count(t_elem *cursor);
char		**ft_elem_get_cmd_args(t_data **data, t_elem *cursor);
t_elem		*ft_elem_get_right(t_elem *cursor);
t_elem		*ft_elem_clone_left(t_elem *cursor);

int			ft_open_double_in(t_elem *list);
int			ft_open_in(t_elem *list);
int			ft_open_redirections(t_elem *list);

/* ************************************************************************** */
/*                                    END                                     */
/* ************************************************************************** */
#endif
