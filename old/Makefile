NAME = minishell
LIBFT = ./libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCD = ./src

SRC = minishell.c \
		ft_env.c \
		ft_lexer.c \

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