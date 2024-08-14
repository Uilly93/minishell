/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_msh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:33:18 by tchalaou          #+#    #+#             */
/*   Updated: 2024/08/14 16:06:46 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*lexing(char *line, t_env *env)
{
	t_token	*token;
	t_token	*add;
	int		i;

	token = NULL;
	i = -1;
	while (line[++i])
	{
		add = create_token(env);
		if (!add)
			return (NULL);
		fill_token(add, line, &i);
		if (!add->id)
		{
			free_token(&add);
			break ;
		}
		token_add_back(&token, add);
	}
	return (token);
}

t_msh	*parsing(t_token *token, t_env *env)
{
	t_msh	*msh;
	t_msh	*add;
	int		i;

	msh = NULL;
	i = -1;
	while (token)
	{
		add = create_msh(++i, env);
		if (!add)
			return (NULL);
		if (fill_msh(add, &token))
		{
			free_msh(&add);
			free_msh(&msh);
			return (NULL);
		}
		msh_add_back(&msh, add);
	}
	return (msh);
}

t_msh	*get_msh(char *line, t_env *env)
{
	t_token	*token;
	t_msh	*msh;

	token = lexing(line, env);
	free(line);
	if (!token)
		return (NULL);
	msh = parsing(token, env);
	free_token(&token);
	return (msh);
}
