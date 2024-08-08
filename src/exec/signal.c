/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:10:45 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/08 10:34:06 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <signal.h>

// void signal_handler(int sig, siginfo_t *info, void *context)
// {
// 	(void)info;
// 	(void)context;
// 	if(sig == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		rl_done = 1;
// 		g_last_sig = SIGINT;
// 	}
// 	else if(sig == SIGQUIT)
// 		g_last_sig = SIGQUIT;
// }

// void void_func(void)
// {
// 	return ;
// }

// int init_signals()
// {
// 	struct sigaction sa;

// 	sa.sa_sigaction = signal_handler;
// 	sigemptyset(&sa.sa_mask);
// 	sa.sa_flags = SA_SIGINFO;
// 	rl_event_hook = (void *)void_func;

// 	if (sigaction(SIGINT, &sa, NULL) == -1)
// 	{
// 		perror("sigaction failed for SIGINT");
// 		return (1);
// 	}

// 	sa.sa_handler = SIG_IGN; // Ignorer SIGQUIT dans le processus parent
// 	if (sigaction(SIGQUIT, &sa, NULL) == -1)
// 	{
// 		perror("sigaction failed for SIGQUIT");
// 		return (1);
// 	}
// 	return (0);
// }

void exec_signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_last_sig = sig;
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", 19);
		// rl_done = true;
		// exit(1);
	}
}

void setup_exec_signals()
{
	struct sigaction sa;

	g_last_sig = 0;
	sa.sa_sigaction = exec_signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;

	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("sigaction failed for SIGQUIT");
		return;
	}
}