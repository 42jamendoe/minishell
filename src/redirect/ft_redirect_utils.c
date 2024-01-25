/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luaraujo <luaraujo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/08/08 20:20:50 by luaraujo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	ft_deal_with_out(int pipe_fd[2], int output)
{
	if (output < 0)
	{
		ft_putendl_fd("minishell: No such file or directory", STDERR_FILENO);
		g_status = 1;
		return (EXIT_FAILURE);
	}
	else
	{
		close(pipe_fd[1]);
		close(STDOUT_FILENO);
		dup2(output, STDOUT_FILENO);
		close(output);
	}
	return (EXIT_SUCCESS);
}

void	ft_check_redir_out(t_cmd *crt_cmd, int pipe_fd[2])
{
	int	output;

	output = 0;
	while (crt_cmd->redir)
	{
		if (crt_cmd->redir->name == GREAT || crt_cmd->redir->name == GREATGREAT)
		{
			if (crt_cmd->redir->name == GREAT)
				output = open(crt_cmd->redir->token_str, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				output = open(crt_cmd->redir->token_str, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		if (ft_deal_with_out(pipe_fd, output))
		{
			close(pipe_fd[1]);
			break ;
		}
		crt_cmd->redir = crt_cmd->redir->next;
	}
}
