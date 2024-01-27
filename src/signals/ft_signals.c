/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 21:40:58 by jamendoe          #+#    #+#             */
/*   Updated: 2023/07/17 21:41:35 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

// void	fork_child(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		ft_putchar_fd('\n', STDOUT_FILENO);
// 		g_status = 130;
// 		exit(130);
// 	}
// }

void	ft_handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status = 130;
	}
}

void	ft_config_signals(t_shell *shell)
{
	struct sigaction	sig_shell;

	if (sigemptyset(&sig_shell.sa_mask))
	{
		ft_clean_exit(shell);
		ft_putendl_fd("error, can't empty sig mask", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (sigaddset(&sig_shell.sa_mask, SIGINT))
	{
		ft_clean_exit(shell);
		ft_putendl_fd("error, can't add sig mask", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	sig_shell.sa_handler = &ft_handle_sigint;
	sig_shell.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_shell, NULL);
	signal(SIGQUIT, SIG_IGN);
}
