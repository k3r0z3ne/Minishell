# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: witong <witong@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/06 18:05:29 by arotondo          #+#    #+#              #
#    Updated: 2024/12/13 15:59:33 by witong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
LIBFT_DIR = libft

SRC = main.c lexer/lexer.c lexer/lexer_utils.c \
		lexer/lexer_utils2.c lexer/lexer_utils3.c \
		lexer/lexer_extract.c lexer/lexer_handler.c \
		parser/parser.c parser/parser_redir.c parser/parser_utils.c
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# SFLAGS = -fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror -g3 -I $(INC_DIR) -I $(LIBFT_DIR)
LIBS = -L $(LIBFT_DIR) -lft -lreadline

DEF_COLOR = \033[0;39m
GREEN = \033[0;92m

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "${GREEN}Compilation of $(NAME) done.${DEF_COLOR}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "${GREEN}Files clean up done.{DEF_COLOR}"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "${GREEN}Clean up done.{DEF_COLOR}"

re: fclean all

.PHONY: all bonus clean fclean re
