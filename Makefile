# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achajar <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/17 17:11:20 by achajar           #+#    #+#              #
#    Updated: 2025/04/17 17:11:22 by achajar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Werror -Wextra

GREEN 	= \033[1;32m
RED		= \033[1;31m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
RC		= \033[0m

NAME_CLIENT = client
NAME_SERVER = server


all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): client.c
	@$(CC) client.c utils.c -o $(NAME_CLIENT)
	@echo "$(GREEN)Client built successfully!$(RC)"

$(NAME_SERVER): server.c
	@$(CC) server.c utils.c -o $(NAME_SERVER)
	@echo "$(BLUE)Server built successfully!$(RC)"

clean:
	@rm -f $(NAME_CLIENT) $(NAME_SERVER)
	@echo "$(YELLOW)Cleaned up!$(RC)"
fclean: clean
	@echo "$(RED)All files are removed!$(RC)"

re: fclean all

.PHONY: clean
