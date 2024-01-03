/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 18:29:07 by jamendoe          #+#    #+#             */
/*   Updated: 2022/11/12 18:29:09 by jamendoe         ###   ########.fr       */
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
# define NO_FD -1

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

extern int	g_status;

typedef enum e_state
{
	DEFAULT,
	SQUOTE,
	DQUOTE,
	DQUOTEOPEN,
}	t_state;

typedef enum e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}	t_builtins;

typedef enum e_token_name
{
	WORD,
	PIPE,
	LESS,
	LESSLESS,
	GREAT,
	GREATGREAT
}	t_token_name;

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
	t_token			*redir;
	int				arg_nbr;
	int				in;
	int				out;
	int				prev_has_redirout;
	pid_t			pid_cmd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_token	*token_list;
	char	**env;
	char	*prompt;
	int		cmd_nbr;
	t_cmd	*command_list;
}	t_shell;

int				ft_loop_prompt(t_shell *shell);
int				ft_check_prompt(char *input);
void			ft_validate_program(t_shell *shell, int argc, char **argv);
void			ft_handle_sigint(int sig);
void			ft_config_signals(t_shell *shell);
int				ft_process_heredoc(t_cmd *current_command, int input, int i);
int				ft_process_file(t_cmd *current_command, int input, int i);
int				ft_check_redir_in(t_cmd *current_command);
int				ft_check_redir_out(t_cmd *crt_cmd, int tmp_pipe[2]);
void			ft_build_redirection_list(t_shell *shell, t_cmd *command);
void			ft_build_simple_command(t_shell *shell, int i, t_cmd *command);
void			ft_create_command(t_shell *shell, t_cmd *command);
void			ft_add_command(t_shell *shell, t_cmd *command);
int				ft_parser(t_shell *shell);
void			ft_check_redir(t_cmd *current_command);
int				ft_command_args_number(t_token *index);
void			ft_clean_pipe_token(t_shell *shell);
int				ft_check_function(char *str);
int				ft_create_token(t_shell *shell, int i, t_token_name name);
int				ft_get_word(t_shell *shell, int i, int j);
int				ft_next_stop(t_shell *shell, int i, int j);
int				ft_create_word(t_shell *shell, int i, t_token_name name);
int				ft_lexer(t_shell *shell);
void			ft_add_new(t_shell *shell, t_token *new_token);
t_token			*ft_create_item(char *token_char, t_token_name token_name);
int				ft_handle_quotes(char *prompt, int i, int c);
int				ft_command_number(t_shell *shell);
t_token_name	ft_check_char(char *prompt, int i);
char			*ft_exp_command(t_shell *shell, char *tmp_word, \
char *to_expand, int *position);
void			ft_delete_redir_invalid(t_cmd *tmp_cmd, t_token *invalid);
int				ft_exp_redir(t_shell *shell, t_cmd *tmp_cmd);
int				ft_expander(t_shell *shell);
char			*ft_expand_dollar(t_shell *shell, char *arg, \
int anchor, int *position);
char			*ft_expand_text(char *arg, int anchor, int *position);
char			*ft_expand_var(t_shell *shell, char *arg, \
int anchor, int *position);
char			*ft_get_env_value(char *env);
int				ft_run_executor(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2]);
int				ft_prepare_executor(t_shell *shell, int backup[2]);
int				ft_finish_executor(t_shell *shell, t_cmd *tmp_cmd, \
int backup[2], int reset);
int				ft_executor(t_shell *shell);
int				ft_handle_left_side(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2]);
int				ft_handle_right_side(t_shell *shell, \
t_cmd *tmp_cmd, int tmp_pipe[2], int backup[2]);
int				ft_run_builtin(t_shell *shell, t_cmd *tmp_cmd);
char			**ft_get_paths(t_shell *shell);
void			ft_fork(t_shell *shell, t_cmd *tmp_cmd, int tmp_pipe[2], int backup[2]);
int				ft_run_command(t_shell *shell, t_cmd *tmp_cmd, int tmp_pipe[2], int backup[2]);
int				ft_check_token_valid(t_shell *shell);
void			ft_check_token_end_last(t_shell *shell, int i);
int				ft_check_token_end(t_shell *shell);
void			ft_print_error(int msg);
int				ft_check_syntax(t_shell *shell);
int				ft_remove_spaces(char *check, int i);
int				ft_check_double_pipe(t_shell *shell);
int				ft_check_quotes_number(t_shell *shell);
int				ft_change_quotes_state(int c, int sqt, int dqt);
int				ft_error_getting_line(t_shell *shell);
int				ft_lexer_err(t_shell *shell);
void			ft_prepare_env(t_shell *shell, char **envp);
int				ft_create_env(t_shell *shell, char **env);
char			*get_sys_binpath(t_shell *shell, t_cmd *tmp_cmd);
char			*ft_search_cmd(t_shell *shell, t_cmd *tmp_cmd);
void			ft_run_cmd_lib(t_shell *shell);
void			ft_execute_cmd(t_shell *shell, t_cmd *tmp_cmd);
void			ft_clean_token(t_token *token_to_clean);
void			ft_clean_char(char **char_to_clean);
void			ft_clean_command(t_cmd *cmd_to_clean);
void			ft_clean(t_shell *shell, int error);
void			ft_clean_env(t_shell *shell);
int				ft_clean_prompt(t_shell *shell);
void			ft_clean_exit(t_shell *shell);
int				ft_exit_mem_error(t_shell *shell, int msg);
void			ft_clean_env_invalid(char **list, int i);
void			ft_change_env_path(t_shell *shell, char *newd, char *path);
void			ft_print_error_cd(char *directory);
int				ft_count_arg_sim_cmd(char **args);
int				ft_cd(t_shell *shell, t_cmd *tmp_cmd);
int				ft_valid_option(t_cmd *tmp_cmd);
int				ft_echo(t_cmd *tmp_cmd);
int				ft_env(t_shell *shell);
int				ft_check_exit_arg(char *arg);
void			ft_get_exit_arg(char *arg);
void			ft_exit(t_shell *shell, t_cmd *tmp_cmd);
int				ft_check_env_item(t_shell *shell, char *arg, int *i);
int				ft_first_digit(char *arg);
char			**ft_prepare_env_arg(char **env);
int				ft_validate_arg_export(char **env);
int				ft_export(t_shell *shell, t_cmd *tmp_cmd);
int				ft_list_lenght(t_shell *shell);
int				ft_transf_vars(t_shell *shell, char **new_env, \
int valid, int z);
void			ft_add_new_vars(t_shell *shell, t_cmd *tmp_cmd, char **new_env);
int				ft_env_with_declare(t_shell *shell);
void			ft_export_var(t_shell *shell, t_cmd *tmp_cmd, int *indexes);
int				ft_pwd(void);
char			**ft_build_new_env(t_shell *shell, char **env, int j);
int				ft_arg_validate_unset(char **env);
int				ft_validate_name(char *arg);
int				ft_validate_arg_unset(char **env);
int				ft_unset(t_shell *shell, t_cmd *tmp_cmd);
int				ft_str_is_env(char *env_itens, char *env_to_test);
int				ft_adjust_list(char *const *shell_list, \
char **new_env, int i, int k);
void			ft_loop_list(char **shell_list, char **unset_list, \
char **new_env);
int				ft_check_list(t_shell *shell, char **env_unset);
int				ft_position_of_equal(char *arg);
int				ft_clean_memory(t_shell *shell, int fd);
void			ft_init_count_redir(t_cmd *tmp_cmd);
char			*ft_expand_dollar_sign_00(t_shell *shell, \
char *str, int *index);
char			*ft_expand_dollar_sign_01(t_shell *shell, \
char *str, int *index);
char			*ft_expand_dollar_sign_1_(t_shell *shell, \
char *str, int *index);
char			*ft_expand_dollar_sign_11(t_shell *shell, \
char *str, int *index);
void			ft_change_quote_state_begin(char *str, \
int *index, int quotes[2]);
void			ft_change_quote_state_end(char *str, \
int *index, int quotes[2]);
char			*ft_test_change_state(t_shell *shell, \
char *to_expand, int *position, int quotes[2]);
char			*ft_join_not_null(char *join, char *expanded);
int				ft_loop_tmp_word(t_shell *shell, t_cmd *tmp_cmd);
int				ft_handle_left_side_noredir(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2]);
int				ft_handle_right_side_noredir(t_shell *shell, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2]);
char	*get_sys_binpath(t_shell *shell, t_cmd *tmp_cmd);
void	ft_run_cmd_lib(t_shell *shell);
#endif
