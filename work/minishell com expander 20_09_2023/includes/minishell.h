/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:43:59 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 16:16:11 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# define GENERAL 1
# define NBR_FUNCTIONS 7

# include <stdlib.h>
# include "libft.h"
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <editline/readline.h>

typedef enum e_status{
	DEFAULT,
	SQUOTE,
	DQUOTE
}	t_status;

typedef enum e_cmd_ft{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_cmd_ft;

typedef enum e_tkn_tp{
	WORD,
	PIPE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT
}	t_tkn_tp;

typedef struct s_token
{
	char			*token;
	t_tkn_tp		type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**sim_cmd;
	t_cmd_ft		function_name;
	t_token			*redir;
	int				arg_nbr;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env_list;
	t_token	*tkn_list;
	t_cmd	*cmd_list;
	t_cmd	*cmd_list_exp;
	char	*prompt;
}	t_shell;

void		ft_clean_env_list(t_shell *shell);
void		ft_add_new_item(t_shell *shell, t_env *item);
t_env		*ft_new_env_item(char *value);
t_tkn_tp	ft_check_char(char *prompt, int i);
int			ft_create_token(t_shell *shell, int i, t_tkn_tp tmp_tkn);
int			ft_create_word(t_shell *shell, int i);
void		ft_lexer(t_shell *shell);
void		ft_add_new(t_shell *shell, t_token *new_token);
t_token		*ft_create_item(char *str, t_tkn_tp item_type);
int			ft_handle_quotes(char *prompt, int i, int c);
void		ft_build_rediretion_list(t_shell *shell, t_cmd *tmp_cmd);
void		ft_build_simple_command(t_shell *shell, int i, t_cmd *tmp_cmd);
void		ft_create_cmd(t_shell *shell, t_cmd *tmp_cmd);
void		ft_add_cmd(t_shell *shell, t_cmd *tmp_cmd);
void		ft_parser(t_shell *shell);
int			ft_cmd_arg_nbr(t_token *index);
void		ft_pipe_clean(t_shell *shell);
int			ft_validate_cmd(char *str);
void		ft_print(t_shell *shell);
t_status	ft_define_status(char c);
void		ft_expander(t_shell *shell);
char		*ft_expanded_cmd(t_shell *shell, char *str, int position);
char	*ft_expand_dollar(t_shell *t_shell, char *arg, int *anchor, int *position);

#endif
