# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lvasseur <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/22 13:23:40 by lvasseur          #+#    #+#              #
#    Updated: 2019/11/22 13:39:04 by lvasseur         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: make all clean fclean re

NAME = ft_ssl
CC = gcc

SRC_PATH = src/
OBJ_PATH = obj/
INC = -I include/ -I libft/

GCC_FLGS = #-Wall -Wextra -Werror
SRC_NAME = main.c
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) $(GCC_FLGS) $(INC) $(OBJ) libft/libft.a -lm -o $(NAME)
	@echo "$(NAME) created"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(GCC_FLGS) $(INC) -o $@ -c $< -lm

clean:
	@make clean -C libft/
	@rm -fv $(OBJ)
	@rm -rf $(OBJ_PATH)
	@echo "all is clean"

fclean: clean
	@make fclean -C libft/
	@rm -fv $(NAME)
	@echo "$(NAME) deleted"

re: fclean clean all
