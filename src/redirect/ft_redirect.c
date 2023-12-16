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
#include "../includes/minishell.h"

int	ft_process_heredoc(t_cmd *current_command, int input, int i)
{
	char	*buffer;
	char	*end;
	int		hd_fd[2];

	if (i > 0)
		close(input);
	pipe(hd_fd);
	end = current_command->redir->token_str;
	input = hd_fd[0];
	while (1)
	{
		buffer = readline("pipe heredoc> ");
		if (!ft_strncmp(buffer, end, ft_strlen(end) + 1))
			break ;
		ft_putendl_fd(buffer, hd_fd[1]);
	}
	close(hd_fd[1]);
	return (input);
}

int	ft_process_file(t_cmd *current_command, int input, int i)
{
	if (i > 0)
		close(input);
	if (access(current_command->redir->token_str, R_OK) < 0)
	{
		g_status = 2;
		ft_putstr_fd(current_command->redir->token_str, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		return (-1);
	}
	else
		input = open(current_command->redir->token_str, O_RDONLY);
	return (input);
}

int	ft_check_redir_in(t_cmd *current_command)
{
	int	i;
	int	input;

	i = 0;
	input = 0;
	while (current_command->redir)
	{
		if (i > 0)
			close(input);
		if (current_command->redir->name == LESS || \
		current_command->redir->name == LESSLESS)
		{
			if (current_command->redir->name == LESS)
				input = ft_process_file(current_command, input, i);
			else if (current_command->redir->name == LESSLESS)
				input = ft_process_heredoc(current_command, input, i);
			if (input < 0)
				return (-1);
		}
		i++;
		current_command->redir = current_command->redir->next;
	}
	return (input);
}

int	ft_check_redir_out(t_cmd *crt_cmd)
{
	int	i;
	int	output;

	output = 1;
	i = 0;
	if (!crt_cmd->redir)
		return (1);
	while (crt_cmd->redir)
	{
		if (i > 0)
			close(output);
		if (crt_cmd->redir->name == GREAT || crt_cmd->redir->name == GREATGREAT)
		{
			if (crt_cmd->redir->name == GREAT)
				output = open(crt_cmd->redir->token_str, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				output = open(crt_cmd->redir->token_str, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		i++;
		crt_cmd->redir = crt_cmd->redir->next;
	}
	return (output);
}
