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

void	ft_run_cmd_lib(t_shell *shell)
{
	t_cmd	*tmp;
	char	*new;
	char	**path;
	int		i;

	path = ft_get_paths(shell);
	tmp = shell->command_list;
	while (tmp)
	{
		i = 0;
		while (path[i])
		{
			if (access(ft_strjoin(ft_strjoin(path[i], "/"), \
			tmp->sim_cmd[0]), F_OK) != 0)
				i++;
			else
				break ;
		}
		new = ft_strjoin(ft_strjoin(path[i], "/"), tmp->sim_cmd[0]);
		free(tmp->sim_cmd[0]);
		tmp->sim_cmd[0] = new;
		tmp = tmp->next;
	}
}

void ft_run_single_command(t_shell *shell)
{
	pid_t	cmd;

	if (shell->command_list->function_name < 0)
	{
		cmd = fork();
		if (cmd == 0)
		{
			execve(shell->command_list->sim_cmd[0], \
			shell->command_list->sim_cmd, shell->env);
			return ;
		}
		waitpid(cmd, NULL, 0);
	}
	else
		ft_run_builtin(shell, shell->command_list->function_name);
}

void	ft_deal_first_command(t_cmd *tmp_cmd, int first)
{
	if (tmp_cmd->in)
		ft_check_redir_in(tmp_cmd, STDIN_FILENO);
	if (tmp_cmd->out)
		ft_check_redir_out(tmp_cmd, first);
	else if (tmp_cmd->next->in)
		close(first);
	else
	{
		if (dup2(first, STDOUT_FILENO) < 0)
			ft_clean();
		close(first);
	}
}

void	ft_deal_middle_command(t_cmd *tmp_cmd, int left, int right)
{
	if (tmp_cmd->in)
		ft_check_redir_in(tmp_cmd, left);		
	else if (tmp_cmd->prev_has_redirout || tmp_cmd->order_id == 0)
		close(left);
	else
	{
		if (dup2(left, STDIN_FILENO) < 0)
			ft_clean();
		close(left);
	}
	if (tmp_cmd->out)
		ft_check_redir_out(tmp_cmd, right);
	else if (tmp_cmd->next->out || tmp_cmd->order_id == tmp_cmd->arg_nbr - 1)
		close(right);
	else
	{
		if (dup2(right, STDOUT_FILENO) < 0)
			ft_clean();
		close(right);
	}
}

void	ft_exec(t_shell *shell, t_cmd *tmp_cmd, int left, int right)
{
	if (execve(tmp_cmd->sim_cmd[0], tmp_cmd->sim_cmd, shell->env) < 0)
	{
		perror (0);
		exit(127);
	}
		close(left);
		close(right);
}

void	ft_close_main(t_shell *shell, int pipe_fds[][2])
{
	int	i;

	i = 0;
	while (i < shell->cmd_nbr + 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
	i = 0;
	// while(i < shell->cmd_nbr)
	// {
		
	// 	waitpid(cmd[i], &status, 0);
	// 	i++;
	// }
}

int ft_fork(t_shell *shell, t_cmd *tmp_cmd, int pipe_fds[][2])
{
	pid_t	cmd[shell->cmd_nbr];
			
	cmd[tmp_cmd->order_id] = fork();
	if (cmd[tmp_cmd->order_id] < 0)
		ft_clean();
	if (cmd[tmp_cmd->order_id] == 0)
	{			
		ft_close_pipes(shell, tmp_cmd, pipe_fds);
		if (tmp_cmd->order_id < shell->cmd_nbr)
			ft_deal_middle_command(tmp_cmd, pipe_fds[tmp_cmd->order_id][0], pipe_fds[tmp_cmd->order_id + 1][1]);
		else
			ft_deal_middle_command(tmp_cmd, pipe_fds[tmp_cmd->order_id][0], pipe_fds[tmp_cmd->order_id + 1][1]);
		ft_exec(shell, tmp_cmd, pipe_fds[tmp_cmd->order_id][0], pipe_fds[tmp_cmd->order_id + 1][1]);
		exit(EXIT_SUCCESS);
	}
	
	ft_close_main(shell, pipe_fds);
	waitpid(-1, NULL, 0);
	return (0);
}

void	ft_executor(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	int 	pipe_fds[3][2];

	
	tmp_cmd = shell->command_list;
	ft_run_cmd_lib(shell);
	if (shell->cmd_nbr == 1)
		ft_run_single_command(shell);
	else
	{
		ft_create_pipes(shell, pipe_fds);
		while (tmp_cmd)
		{
			ft_fork(shell, tmp_cmd, pipe_fds);

			if (!tmp_cmd->next)
				break;
			tmp_cmd = tmp_cmd->next;
		}
	}
}
		