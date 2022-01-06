# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gadeneux <gadeneux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/14 23:11:43 by cmaginot          #+#    #+#              #
#    Updated: 2022/01/06 17:32:20 by gadeneux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

SRCS=$(addprefix ${FOLDER}/, \
	ft_minishell.c \
	ft_readcmd.c \
	ft_execcmd.c \
	ft_cmdline.c \
	ft_signal_handler.c\
	ft_prompt.c \
	ft_strutils.c \
	ft_env.c \
	ft_check_quote.c)
OBJS=$(SRCS:.c=.o)

FOLDER=srcs
INCLUDES=$(addprefix includes/, \
	ft_minishell.h)

NAME_LIBFT=libft
NAME_GNL=get_next_line
LIBFT=includes/libft
GNL=includes/Get_next_line


CC=clang -g
CFLAGS=-Wall -Wextra -Werror -g3 -fsanitize=address
RM=rm -f

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT) bonus
	make -C $(GNL)
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