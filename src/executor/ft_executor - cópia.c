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

void	ft_executor(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	pid_t	cmd[shell->cmd_nbr];
	int 	pipe_fds[shell->cmd_nbr - 1][2];
	int		status;
	int i = 0;
	int z = 0;

	tmp_cmd = shell->command_list;
	shell->fd_pipe->cmd_position = 1;
	ft_run_cmd_lib(shell);
	if (shell->cmd_nbr == 1)
		ft_run_single_command(shell);
	else
	{
		while(i < shell->cmd_nbr + 1)
		{
			pipe(pipe_fds[i]);
			i++;
		}
		i = 0;
		while(i < shell->cmd_nbr)
		{
			
			cmd[i] = fork();
			if (cmd[i] == 0)
			{
				int j = 0;
				while (j < shell->cmd_nbr)
				{
					if (j == 0)
						close(pipe_fds[1][0]);
					else if (j == shell->cmd_nbr)
						close(pipe_fds[j - 1][1]);
					else
						{
							close(pipe_fds[j][0]);
							close(pipe_fds[j - 1][1]);
						}
				}
				if (tmp_cmd->in)
					ft_check_redir_in(tmp_cmd, pipe_fds[i][0]);
				if (tmp_cmd->prev_has_redirout)
					dup2(pipe_fds[i][0], STDIN_FILENO);
				close(pipe_fds[i][0]);
				if (tmp_cmd->out)
					ft_check_redir_out(tmp_cmd, pipe_fds[i + 1][1]);
				else
					dup2(pipe_fds[i + 1][1], STDOUT_FILENO);
				close(pipe_fds[i + 1][1]);			
			}
			waitpid(cmd[i], &status, 0);
			while (z < shell->cmd_nbr)
			{
				//if (0 != z)
					close(pipe_fds[z][0]);
				//if (shell->cmd_nbr + 1 != z)
					close(pipe_fds[z][1]);
			}
			i++;
			tmp_cmd = tmp_cmd->next;
		}
	}
}
		