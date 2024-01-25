NAME = minishell
LIBFT = ./libft/libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -rf

SRCD = ./src

SRC = minishell.c \
		environment/ft_environment.c \
		lexer/ft_lexer.c \
		lexer/ft_lexer_utils.c \
		parser/ft_parser.c \
		parser/ft_parser_utils.c \
		expander/ft_expander.c \
		expander/ft_expander_utils.c \
		expander/ft_expander_utils2.c \
		expander/ft_expander_utils3.c \
		executor/ft_executor.c \
		executor/ft_executor_utils.c \
		error/ft_error.c \
		error/ft_error_utils.c \
		error/ft_error_utils2.c \
		signals/ft_signals.c \
		redirect/ft_redirect.c \
		redirect/ft_redirect_utils.c \
		builtins/cd/ft_cd.c \
		builtins/pwd/ft_pwd.c \
		builtins/echo/ft_echo.c \
		builtins/env/ft_env.c \
		builtins/exit/ft_exit.c \
		builtins/export/ft_export.c \
		builtins/export/ft_export_utils.c \
		builtins/unset/ft_unset.c \
		builtins/unset/ft_unset_utils.c \
		cmd/ft_cmd.c \
		cmd/ft_cmd_utils.c \
		clean/ft_clean.c \
		clean/ft_clean_utils.c \

OBJ = $(SRC:%.c=$(SRCD)/%.o)

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft -lreadline -o $(NAME)

$(LIBFT):	
	$(MAKE) -C libft

$(SRCD)/%.o: $(SRCD)/%.c
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	$(RM) $(OBJ)
	make -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)

re: fclean all clean

.PHONY: all libft clean fclean re