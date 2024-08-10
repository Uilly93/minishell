/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:40:20 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/10 12:52:42 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msh_loop(t_msh *msh, t_env **env)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		set_global(env);
		prompt = custom_prompt(env);
		if (!prompt)
			line = readline("Prompt not generated> ");
		else
			line = readline(prompt);
		free(prompt);
		if (!line)
			return ((*env)->ex_code);
		if (g_last_sig != SIGINT && ft_strlen(line))
		{
			add_history(line);
			msh = get_msh(line, *env);
			exec(msh, env);
		}
		wait_pids(env);
	}
	return (0);
}
