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

# define FIRST_CMD 8
# define LAST_CMD 9
# define PREV_RED_OUT 1
# define PREV_NOT_RED_OUT 0
# define START 2


# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <sys/wait.h>

typedef enum e_state{
	DEFAULT,
	SQUOTE,
	DQUOTE
}	t_state;

typedef enum e_builtins{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtins;

typedef enum e_token_name{
	WORD,
	PIPE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT
}	t_token_name;

typedef struct s_fd_pipes
{
	int		backup[2];
	int		tmp_fd[2];
	int 	pipe[2];
	int		cmd_position;
}	t_fd_pipes;

typedef struct s_token
{
	char			*token_str;
	t_token_name	name;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**sim_cmd;
	int				function_name;
	int				order_id;
	int				joy_division_transmission[2];
	t_token			*redir;
	int				arg_nbr;
	int				in;
	int				out;
	int				prev_has_redirout;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_token	*token_list;
	char	**env;
	int		cmd_nbr;
	t_cmd	*command_list;
	char	*prompt;
	t_fd_pipes *fd_pipe;
}	t_shell;

int				ft_create_env(t_shell *shell, char **env);
void			ft_config_signals(void);
void			ft_handle_sigint(int sig);
void			ft_lexer(t_shell *shell);
t_token_name	ft_check_char(char *prompt, int i);
int				ft_create_word(t_shell *shell, int i);
int				ft_handle_quotes(char *prompt, int i, int c);
t_token			*ft_create_item(char *token_char, t_token_name name_name);
void			ft_add_new(t_shell *shell, t_token *new_token);
int				ft_command_number(t_shell *shell);
void			ft_parser(t_shell *shell);
int				ft_command_args_number(t_token *index);
void			ft_create_command(t_shell *shell, t_cmd *command);
void			ft_build_simple_command(t_shell *shell, int i, t_cmd *command);
void			ft_build_redirection_list(t_shell *shell, t_cmd *command);
void			ft_clean_pipe_token(t_shell *shell);
void			ft_add_command(t_shell *shell, t_cmd *command);
void			ft_expander(t_shell *shell);
char			*ft_expand_arg(char *arg, int *position);
t_state			ft_define_state(char c);
char			*ft_process_arg(char *arg, int anchor, int position);
char			*ft_expand_text(char *arg, int anchor, int position);
char			*ft_expand_var(char *arg, int anchor, int position);
char			*ft_expand_dollar(char *arg, int anchor, int position);
void 			ft_clean (void);
void			ft_executor(t_shell *shell);
void 			ft_print_elements_token(t_shell *shell);
void 			ft_print_elements_char(t_shell *shell);
void ft_print_elements_redir(t_shell *shell);
void ft_print_arraydocomando(t_shell *shell);
int ft_process_input(t_shell *shell, char *input);
void ft_check_redir(t_cmd *current_command);
int	ft_check_function(char *str);
int	ft_check_function(char *str);
int	ft_echo(t_shell *shell, char **arg);
int ft_position_of_equal(char *arg);

void ft_change_env_path(t_shell *shell, char *newd, char *path);
int	ft_cd(t_shell *shell, char **newd);
int	ft_echo(t_shell *shell, char **arg);
int	ft_env(t_shell *shell);
void	ft_exit(t_shell *shell, char **arg);
int ft_check_env_item(t_shell *shell, char *arg);
int ft_position_of_equal(char *arg);
int	ft_first_digit(char *arg);
int ft_validate_arg(char **env);
int	ft_export(t_shell *shell, char **env);
int	ft_pwd(void);
int ft_str_is_env(char *env_itens, char *env_to_test);
char **ft_build_new_env(t_shell *shell, char **env, int j);
int	ft_arg_validate_unset(char **env);
int	ft_unset(t_shell *shell, char **env);
void ft_run_child(t_shell *shell, t_cmd *current_command, int i);
int	ft_run_builtin(t_shell *shell, int function);
void	ft_check_redir(t_cmd *current_command);
void ft_check_redir_in(t_cmd *current_command, int i);
void ft_check_redir_out(t_cmd *current_command, int i);
void	ft_process_heredoc(char *end);
int	ft_count_redir_in(t_cmd *current_command);
int	ft_count_redir_out(t_cmd *current_command);
void ft_run_cmd(t_shell *shell, t_cmd  *command);
int	ft_create_pipes(t_shell *shell, int pipe_fds[][2]);
int ft_close_pipes(t_shell * shell, t_cmd *tmp_cmd, int pipe_fds[][2]);

#endif
