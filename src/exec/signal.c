/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:10:45 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/09 13:08:54 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	{
		g_last_sig = sig;
	}
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
