void ft_run_child(t_shell *shell, t_cmd *current_command, int restart)
{
	if (execve(command->sim_cmd[0], command->sim_cmd, \
	shell->env))
	{
		perror (0);
		exit(127);
	}
	if (shell->fd_pipe->cmd_position < shell->cmd_nbr)
	{
		if (restart || shell->fd_pipe->cmd_position != 1)
			close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(shell->fd_pipe->tmp_fd[0]);
	}
	else
	{
		if (current_command->out)
			close(STDOUT_FILENO);
		if (!restart || shell->fd_pipe->cmd_position != 1)
			close(STDIN_FILENO);
		close(shell->fd_pipe->tmp_fd[0]);
	}
}

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
	int restart = 0;
	t_cmd	*tmp_cmd;
	pid_t	cmd;
	int		status;

	tmp_cmd = shell->command_list;
	shell->fd_pipe->cmd_position = 1;
	ft_run_cmd_lib(shell);
	if (shell->cmd_nbr == 1)
		ft_run_single_command(shell);
	else
	{
		shell->fd_pipe->backup[0] = dup(STDIN_FILENO);
		shell->fd_pipe->backup[1] = dup(STDOUT_FILENO);
		while(tmp_cmd)
		{
			if (tmp_cmd->in)
				ft_check_redir_in(shell, tmp_cmd);
			else
			{
				if (shell->fd_pipe->cmd_position == 1 || restart == 1)
					dup2(shell->fd_pipe->backup[0], STDIN_FILENO);
				else
					dup2(shell->fd_pipe->tmp_fd[0], STDIN_FILENO);
			}
			pipe(shell->fd_pipe->pipe);
			shell->fd_pipe->tmp_fd[1] = shell->fd_pipe->pipe[1];
			shell->fd_pipe->tmp_fd[0] = shell->fd_pipe->pipe[0];		
			if (shell->fd_pipe->cmd_position < shell->cmd_nbr)
			{	
				if (tmp_cmd->out)
				{
					ft_check_redir_out(shell, tmp_cmd);
					//restart = 1;
				}
				else
				{
					dup2(shell->fd_pipe->tmp_fd[1], STDOUT_FILENO);
					//close(shell->fd_pipe->tmp_fd[1]);
					//write(shell->fd_pipe->backup[1], "correu\n", sizeof("correu\n"));
					//restart = 0;
				}
			}
			else
			{
				if (tmp_cmd->out)
				{
					ft_check_redir_out(shell, tmp_cmd);
					restart = 1;
				}
				else
				{
					dup2(shell->fd_pipe->backup[1], STDOUT_FILENO);
				}
			}
			write(shell->fd_pipe->backup[1], "antes do fork\n", sizeof("antes do fork\n"));
			cmd = fork();	
			if (cmd == 0)
				ft_run_child(shell, tmp_cmd, restart);
			waitpid(cmd, &status, 0);
			write(shell->fd_pipe->backup[1], "depois do fork\n", sizeof("depois do fork\n"));
			if (shell->fd_pipe->cmd_position < shell->cmd_nbr)
			{
				shell->fd_pipe->tmp_fd[1] = STDOUT_FILENO;
				close(STDOUT_FILENO);
				if (restart > 0)
					dup2(STDIN_FILENO, shell->fd_pipe->backup[0]);
				else
					close(STDIN_FILENO);
				restart = 0;				
				if (tmp_cmd->next->in)
				{
					close(shell->fd_pipe->tmp_fd[0]);
					restart = 1;
				}
			}
			else
			{
				close(STDIN_FILENO);
				if (tmp_cmd->out)
					close(STDOUT_FILENO);
				else
					dup2(STDOUT_FILENO, shell->fd_pipe->backup[1]);
			}
			shell->fd_pipe->cmd_position++;
			tmp_cmd = tmp_cmd->next;
		}
		dup2(shell->fd_pipe->backup[0], STDIN_FILENO);
		dup2(shell->fd_pipe->backup[1], STDOUT_FILENO);
	}
	write(shell->fd_pipe->backup[0], "encerrou\n", sizeof("encerrou\n"));
}
