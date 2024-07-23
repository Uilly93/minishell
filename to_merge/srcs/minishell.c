/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:14:30 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/23 15:38:50 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_msh	*get_msh(char *line, t_env *env)
{
	t_token *token;
	t_msh	*msh;
	
	token = lexing(line, env);
	free(line);
	if (!token)
		return (NULL);
	msh = parsing(token);
	free_token(&token);
	return (msh);
}

int	main(void)
{
	char	*line;
	t_env	*env;
	t_msh	*msh;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	env = get_env();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (!ft_strlen(line))
			continue ;
		add_history(line);
		msh = get_msh(line, env);
		if (!msh)
			continue ;
		execute(msh);
		free_msh(&msh);
	}
	free_env(&env);
	return (0);
}
