#!/usr/bin/make -f
NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I libft/inc
LIBFT = libft/libft.a
SRC = \
	builtin_cd\
	builtin_echo\
	builtin_env\
	builtin_exit\
	builtins\
	env\
	execute\
	main\
	parse\
	util\
	vars
OBJ = $(patsubst %, %.o, $(SRC))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "Building $@..."
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $@
	@echo "Done."

$(LIBFT):
	@echo "Building $@..."
	@make -C libft

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ)
	@make -C libft clean
	@echo "Object files removed."

fclean: clean
	@rm -f $(NAME)
	@make -C libft fclean
	@echo "$(NAME) removed."

re: fclean all
