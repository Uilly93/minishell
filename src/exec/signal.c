/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 09:10:45 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/07 11:50:46 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>

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

void child_signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	ft_printf(1, "Quit (core dumped)\n");
	g_last_sig = SIGQUIT;
	rl_done = true;
	// exit(1);
}

void setup_child_signals()
{
	struct sigaction sa;
	
	sa.sa_handler = SIG_DFL; // change this
	g_last_sig = 0;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = child_signal_handler;
	sa.sa_flags = SA_SIGINFO;

    if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
        perror("sigaction failed for SIGQUIT");
        return ;
    }
}