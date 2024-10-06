# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dramos-j <dramos-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 12:44:31 by dramos-j          #+#    #+#              #
#    Updated: 2024/10/05 16:53:23 by dramos-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT = client
NAME_SERVER = server
FT_PRINTF = ./ft_printf
FT_PRINTF_LIB = ./ft_printf/libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS_CLIENT = client.c
SRCS_SERVER = server.c
OBJS_CLIENT = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER = $(SRCS_SERVER:.c=.o)
RM = rm -rf

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(MAKE) -C $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_CLIENT) $(OBJS_CLIENT) $(FT_PRINTF_LIB)

$(NAME_SERVER): $(OBJS_SERVER)
	$(MAKE) -C $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME_SERVER) $(OBJS_SERVER) $(FT_PRINTF_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(FT_PRINTF) clean
	$(RM) $(OBJS_CLIENT) $(OBJS_SERVER)

fclean: clean
	$(MAKE) -C $(FT_PRINTF) fclean
	$(RM) $(NAME_CLIENT) $(NAME_SERVER)

re: fclean all

.PHONY: all clean fclean re
.SILENT:
