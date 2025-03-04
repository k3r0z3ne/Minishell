NAME = minishell
CC = cc

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes
LIBFT_DIR = libft

SRC =	main.c utils/init.c \
		lexer/lexer.c lexer/lexer_input.c lexer/lexer_illegal.c \
		lexer/lexer_token.c lexer/lexer_utils.c\
		lexer/lexer_extract.c lexer/lexer_handler.c \
		executor/execution.c executor/path.c \
		executor/exec_utils.c executor/exec_utils2.c \
		executor/redirection.c executor/here_doc.c \
		executor/one_command.c executor/several_commands.c \
		executor/redirection2.c \
		builtins/cd.c builtins/cd_utils.c builtins/echo.c builtins/env.c \
		builtins/exit.c builtins/exit_utils.c builtins/export.c \
		builtins/export_utils.c \
		builtins/pwd.c builtins/unset.c builtins/env_utils.c \
		parser/parser.c parser/parser_init.c parser/parser_redirs.c \
		parser/parser_utils.c parser/parser_error.c \
		expander/expand.c expander/expand_utils.c \
		utils/global_utils.c utils/gc.c utils/signals.c \
		utils/error.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)

# SFLAGS = -fsanitize=address -g
CFLAGS = -Wall -Wextra -Werror -I $(INC_DIR) -I $(LIBFT_DIR)
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
	@echo "${GREEN}Files clean up done.${DEF_COLOR}"

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME) $(NAME_BONUS)
	@echo "${GREEN}Clean up done.${DEF_COLOR}"

re: fclean all

.PHONY: all bonus clean fclean re
