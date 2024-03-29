# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmaginot <cmaginot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/20 19:17:29 by cmaginot          #+#    #+#              #
#    Updated: 2022/03/18 16:21:29 by cmaginot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRCS=$(addprefix ${FOLDER}/, \
	ft_minishell.c \
	ft_run_line.c \
	ft_read_line.c \
	ft_read_cmd.c \
	ft_run_execve.c \
	ft_signal_handler.c \
	ft_tools_error.c \
	ft_tools_error_type.c \
	ft_tools_env.c \
	ft_tools_quote.c \
	ft_tools_operator.c \
	ft_tools_is_executable.c \
	ft_bi.c \
	ft_bi_cd.c \
	ft_bi_cd_2.c \
	ft_bi_echo.c \
	ft_bi_env.c \
	ft_bi_export.c \
	ft_bi_export2.c \
	ft_bi_pwd.c \
	ft_bi_unset.c \
	ft_bi_exit.c \
	ft_tools_elem.c \
	ft_tools_free_lsts.c \
	ft_tools_char.c \
	ft_tools_str_create.c \
	ft_tools_str_get_index.c \
	ft_tools_str_replace.c \
	ft_tools_redirection_in.c \
	ft_tools_redirection_out.c \
	ft_tools_syntaxe.c \
	ft_tools_access.c \
	ft_tools_access_mute.c \
	ft_v2_executions.c \
	ft_v2_executions_2.c \
	ft_v2_executions_3.c \
	ft_v2_executions_4.c \
	ft_v2_redirections.c \
	ft_v2_redirections2.c \
	ft_v2_tools_redirections.c \
	ft_v2_tools_redirections_2.c \
	ft_v2_tools_env.c \
	ft_v2_tools_env2.c \
	ft_v2_tools_env3.c \
	ft_v2_expension.c \
	ft_v2_expension_2.c \
	ft_v2_expension_3.c \
	ft_v2_heredoc.c \
	ft_tools_strs.c)
OBJS=$(SRCS:.c=.o)

FOLDER=srcs
INCLUDES=$(addprefix includes/, \
	ft_minishell.h)

NAME_LIBFT=libft
NAME_GNL=get_next_line
LIBFT=includes/libft
GNL=includes/Get_next_line


CC=clang -g
CFLAGS=-Wall -Wextra -Werror -g3 #-fsanitize=address
RM=rm -f

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT) bonus
	make -C $(GNL) bonus
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT)/libft.a $(GNL)/get_next_line.a -lreadline

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $< -I $(INCLUDES)

clean:
	make clean -C $(LIBFT)
	make clean -C $(GNL)
	$(RM) $(OBJS)

fclean: clean
	make fclean -C $(LIBFT)
	make fclean -C $(GNL)
	$(RM) $(NAME)


re: fclean all
