/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	ft_process_heredoc(t_cmd *current_command, int *pipe_r)
{
	char	*buffer;
	char	*end;
	int		hd_fd[2];

	close((*pipe_r));
	pipe(hd_fd);
	(*pipe_r) = dup(hd_fd[0]);
	close(hd_fd[0]);
	end = current_command->redir->token_str;
	while (1)
	{
		buffer = readline("pipe heredoc> ");
		if (!ft_strncmp(buffer, end, ft_strlen(end) + 1))
			break ;
		ft_putendl_fd(buffer, hd_fd[1]);
	}
	close(hd_fd[1]);
	return (EXIT_SUCCESS);
}

int	ft_process_file(t_cmd *current_command, int *pipe_r)
{
	int	fd;

	if (access(current_command->redir->token_str, R_OK) < 0)
	{
		g_status = 1;
		ft_putstr_fd(current_command->redir->token_str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else
	{
		fd = open(current_command->redir->token_str, O_RDONLY);
		close((*pipe_r));
		dup2(fd, (*pipe_r));
		close(fd);
	}
	return (EXIT_SUCCESS);
}

int	ft_open_in_file(t_cmd *cmd, int pipe_r)
{
	int	pipe_redir[2];
	int	fd;

	fd = -1;
	close(pipe_r);
	pipe_r = ft_fake_open(pipe_redir);
	if (cmd->redir->name == LESS || \
	cmd->redir->name == LESSLESS)
	{
		if (cmd->redir->name == LESS)
			fd = ft_process_file(cmd, &pipe_r);
		else
			fd = ft_process_heredoc(cmd, &pipe_r);
	}
	return (fd);
}

int	ft_fake_open(int input[2])
{
	int	pipe_r;

	pipe(input);
	pipe_r = dup(input[0]);
	close(input[0]);
	close(input[1]);
	return (pipe_r);
}

void	ft_check_redir_in(t_cmd *cmd, int pipe_fd[2])
{
	int	pipe_r;
	int	pipe_backup[2];

	pipe_r = ft_fake_open(pipe_backup);
	while (cmd->redir)
	{
		ft_open_in_file(cmd, pipe_r);
		if (!cmd->redir->next)
			break ;
		cmd->redir = cmd->redir->next;
	}
	if (cmd->order_id == 0 && !cmd->redir)
		close(STDIN_FILENO);
	else
		close(pipe_fd[0]);
	dup2(pipe_r, STDIN_FILENO);
	close(pipe_r);
	close(pipe_fd[1]);
}
