NAME = minishell
LIBFT = ./libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -g#-fsanitize=address
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
		executor/ft_executor.c \
		executor/ft_executor_utils.c \
		redirect/ft_redirect.c \
		builtins/cd/ft_cd.c \
		builtins/pwd/ft_pwd.c \
		builtins/echo/ft_echo.c \
		builtins/env/ft_env.c \
		builtins/exit/ft_exit.c \
		builtins/export/ft_export.c \
		builtins/unset/ft_unset.c \
		cmd/ft_cmd.c \

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