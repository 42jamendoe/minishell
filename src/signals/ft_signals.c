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

void	fork_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		g_status = 130;
		exit(130);
	}
}

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

void	ft_config_signals(void)
{
	struct sigaction	sig_shell;

	sig_shell.sa_handler = ft_handle_sigint;
	sig_shell.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_shell, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_handle_sigint_in_child(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_status = 130;
	}
}

void	ft_config_signals_in_child(void)
{
	struct sigaction	sig_shell_in_child;

	sig_shell_in_child.sa_handler = ft_handle_sigint_in_child;
	sig_shell_in_child.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sig_shell_in_child, NULL);
	signal(SIGQUIT, SIG_IGN);
}
