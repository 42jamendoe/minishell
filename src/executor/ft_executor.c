/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

extern long long	g_status;

char	**ft_get_paths(t_shell *shell)
{
	int		i;
	char	*paths_char;
	char	**splited;

	i = 0;
	splited = NULL;
	while (shell->env[i])
	{
		if (shell->env[i] && ft_strncmp(shell->env[i], "PATH=", 5))
			i++;
		else
		{
			paths_char = ft_substr(shell->env[i], 5, \
			ft_strlen(shell->env[i]) - 5);
			splited = ft_split(paths_char, ':');
			return (splited);
		}
	}
	return (NULL);
}

void	ft_handle_left_side(int cmd_nbr, t_cmd *tmp_cmd, \
int tmp_pipe[2], int backup[2])
{
	if (tmp_cmd->in)
	{
		tmp_pipe[0] = ft_check_redir_in(tmp_cmd);
		dup2(tmp_pipe[0], STDIN_FILENO);
		close(tmp_pipe[0]);
	}
	else
	{
		if (!tmp_cmd->order_id || !tmp_cmd->prev_has_redirout)
		{
			if (!tmp_cmd->order_id )
			{
				tmp_pipe[0] = STDIN_FILENO;
				// pipe(tmp_pipe);
				// close(tmp_pipe[1]);
				// dup2(tmp_pipe[0], STDIN_FILENO);
				// close(tmp_pipe[0]);
			}
			else
			{
				dup2(tmp_pipe[0] , STDIN_FILENO);
				close(tmp_pipe[0]);
				pipe(tmp_pipe);
				close(tmp_pipe[1]);
			}

		}
		else if (tmp_cmd->prev_has_redirout)
		{
			dup2(backup[0], tmp_pipe[0]);
			dup2(tmp_pipe[0], STDIN_FILENO);
			close(tmp_pipe[0]);
		}
		// else
		// 	tmp_pipe[0] = tmp_pipe[0];
	}
	if (tmp_cmd->order_id == cmd_nbr - 1)
	{
		tmp_pipe[1] = STDOUT_FILENO;		
		if (tmp_cmd->out)
			tmp_pipe[1] = ft_check_redir_out(tmp_cmd);
		else
			dup2(backup[1], tmp_pipe[1]);
		dup2(tmp_pipe[1], STDOUT_FILENO);
		//close(tmp_pipe[1]);
	}
}

void	ft_handle_right_side(t_cmd *tmp_cmd, int tmp_pipe[2])
{
	//int	next_input[2];

	if (tmp_cmd->next->in)
		tmp_pipe[1] = tmp_pipe[1];
	else
	{
		if (tmp_cmd->out)
			tmp_pipe[1] = ft_check_redir_out(tmp_cmd);
		else
		{
			pipe(tmp_pipe);
			// tmp_pipe[1] = next_input[1];
		}
	}
	dup2(tmp_pipe[1], STDOUT_FILENO);
	close(tmp_pipe[1]);
}

void	ft_run_command(t_shell *shell, t_cmd *tmp_cmd)
{
	pid_t	cmd;
	int		status;

	status = 0;
	if (shell->command_list->function_name > 0 && \
	!shell->command_list->redir && shell->cmd_nbr == 1)
	{
		ft_run_builtin(shell, tmp_cmd);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	else
	{
		cmd = fork();
		if (cmd < 0)
			ft_clean(shell, 1);
		if (cmd == 0)
		{
			ft_execute_cmd(shell, tmp_cmd);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			exit (EXIT_SUCCESS);
		}
		waitpid(cmd, &status, 0);
		if (!WTERMSIG(status))
			g_status = status >> 8;
	}
}

void	ft_executor(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int		backup[2];
	int		tmp_pipe[2];

	tmp_cmd = shell->command_list;
	backup[0] = dup(STDIN_FILENO);
	backup[1] = dup(STDOUT_FILENO);
	while (tmp_cmd)
	{
		ft_handle_left_side(shell->cmd_nbr, tmp_cmd, tmp_pipe, backup);
		if (tmp_cmd->order_id != shell->cmd_nbr - 1)
			ft_handle_right_side(tmp_cmd, tmp_pipe);
		ft_run_command(shell, tmp_cmd);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		dup2(backup[0], STDIN_FILENO);
		dup2(backup[1], STDOUT_FILENO);
		if (!tmp_cmd->next)
			break ;
		tmp_cmd = tmp_cmd->next;
	}
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	close(backup[0]);
	close(backup[1]);
}
