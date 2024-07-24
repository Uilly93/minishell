/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:24:26 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/24 15:57:20 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_msh	*create_msh(int index, t_env *env)
{
	t_msh	*msh;

	msh = ft_calloc(sizeof(t_msh), 1);
	if (!msh)
		return (NULL);
	msh->env = env;
	msh->pipefd[0] = -1;
	msh->pipefd[1] = -1;
	msh->index = index + 1;
	msh->in = -1;
	msh->out = -1;
	return (msh);
}

int	count_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->id == WORD)
	{
		count++;
		token = token->next;
	}
	return (count);
}

t_msh	*msh_get_last(t_msh *msh)
{
	t_msh	*current;

	if (!msh)
		return (0);
	current = msh;
	while (current->next)
		current = current->next;
	return (current);
}

void	msh_add_back(t_msh **msh, t_msh *add)
{
	t_msh	*last;

	if (!add)
		return ;
	if (!*msh)
		*msh = add;
	else
	{
		last = msh_get_last(*msh);
		last->next = add;
		add->prev = last;
	}
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_msh(t_msh **msh)
{
	t_msh	*current;

	while (*msh)
	{
		current = *msh;
		*msh = current->next;
		if (current->cmd)
			free_array(current->cmd);
		if (current->infile)
			free(current->infile);
		if (current->outfile)
			free(current->outfile);
		free(current);
	}
}
