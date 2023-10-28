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

void	ft_process_heredoc(char *end)
{
	char	*buffer;
	int		fd_lines[2];

	pipe(fd_lines);
	while (1)
	{
		buffer = readline("> ");
		if (!ft_strncmp(buffer, end, ft_strlen(end) + 1))
			break ;
		ft_putendl_fd(buffer, fd_lines[1]);
	}
	close(fd_lines[1]);
	dup2(fd_lines[0], STDIN_FILENO);
	close(fd_lines[0]);
	free(buffer);
}

void ft_check_redir_in(t_cmd *current_command, int i)
{
	while (current_command->redir)
	{
		if(current_command->redir->name == LESS)
		{
			//close(STDIN_FILENO);
			if (access(current_command->redir->token_str, R_OK) < 0)
			{
				ft_putstr_fd(current_command->redir->token_str, STDERR_FILENO);
				ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			}
			else
			{
				i = open(current_command->redir->token_str, O_RDONLY);
				if (dup2(i, STDIN_FILENO) < 0)
					ft_putstr_fd("error with redirection file\n", STDERR_FILENO);
				close(i);
			}
		}
		else if(current_command->redir->name == LESSLESS)
			ft_process_heredoc(current_command->redir->token_str);
		current_command->redir = current_command->redir->next;
	}
}

void ft_check_redir_out(t_cmd *current_command, int i)
{
	while (current_command->redir)
	{
		if(current_command->redir->name == GREAT || current_command->redir->name == GREATGREAT)
		{
			//close(STDOUT_FILENO);
			if (current_command->redir->name == GREAT)
				i = open(current_command->redir->token_str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				i = open(current_command->redir->token_str, O_CREAT | O_WRONLY | O_APPEND, 0644);
			dup2(i, STDOUT_FILENO);
			close(i);	
		}
		current_command->redir = current_command->redir->next;
	}
}


