/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:10:45 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/14 14:05:03 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	rl_done = true;
	g_last_sig = SIGINT;
}

void	null_func(void)
{
	return ;
}

int	init_sigint(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	rl_event_hook = (void *)null_func;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction failed for SIGINT");
		return (1);
	}
	sa.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction failed for SIGQUIT");
		return (1);
	}
	return (0);
}

void	exec_signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGQUIT)
	{
		g_last_sig = sig;
		write(2, "Quit (core dumped)\n", 19);
		rl_done = true;
	}
	if (sig == SIGINT)
		g_last_sig = sig;
}

void	setup_exec_signals(void)
{
	struct sigaction	sa;

	g_last_sig = 0;
	sa.sa_sigaction = exec_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction failed for SIGQUIT");
		return ;
	}
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("sigaction failed for SIGQUIT");
		return ;
	}
}
