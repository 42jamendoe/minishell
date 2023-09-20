NAME = minishell
LIBFT = ./libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -rf

SRCD = ./src

SRC = minishell.c \
		environment/ft_env.c \
		lexer/ft_lexer.c \
		lexer/ft_lexer_utils.c \
		parser/ft_parser.c \
		parser/ft_parser_utils.c \
		expander/ft_expander.c \
		expander/ft_expander_utils.c \

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