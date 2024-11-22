# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macbook <macbook@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 21:29:54 by macbook           #+#    #+#              #
#    Updated: 2024/11/22 01:08:59 by macbook          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Werror -Wextra
MAKE_LIB = ar -rcs

NAME = minitalk
NAME_SERVER = server
NAME_CLIENT = client

PRINTF_DIR = ./ft_printf
PRINTF = $(PRINTF_DIR)/libftprintf.a

SRCS_SERVER = server.c \
              utils.c

SRCS_CLIENT = client.c \
              utils.c

OBJS_SERVER = $(SRCS_SERVER:.c=.o)
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)

all: $(NAME)

$(NAME): $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(PRINTF) $(OBJS_SERVER)
	$(CC) $(CFLAGS) -o $@ $(OBJS_SERVER) -L$(PRINTF_DIR) -lftprintf

$(NAME_CLIENT): $(PRINTF) $(OBJS_CLIENT)
	$(CC) $(CFLAGS) -o $@ $(OBJS_CLIENT) -L$(PRINTF_DIR) -lftprintf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(PRINTF):
	$(MAKE) -C $(PRINTF_DIR)

clean:
	rm -f $(OBJS_SERVER) $(OBJS_CLIENT)
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re