/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:04:34 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/14 13:53:35 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/history.h>

int	g_last_sig;

int	main(void)
{
	t_msh		msh;
	t_env		**env;
	extern char	**environ;
	int			last_exit_code;

	env = NULL;
	env = env_into_list(environ);
	if (!env || !*env)
		return (1);
	ft_bzero(&msh, sizeof(t_msh));
	msh_loop(&msh, env);
	clear_history();
	last_exit_code = (*env)->ex_code;
	free_env(env);
	return (last_exit_code);
}
