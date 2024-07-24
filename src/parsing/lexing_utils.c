/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:15:51 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/24 14:23:42 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(t_env *env)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->id = -1;
	token->word = NULL;
	token->env = env;
	token->next = NULL;
	return (token);
}

int	is_whitespace(char c)
{
	return (c != ' ' && c != '\t' && c != '\v' && c != '\n');
}

int	word_len(char *line, int start)
{
	int	len;

	len = 0;
	while (line[start] && !ft_strchr(" \t\n;<>|'\"", line[start]))
	{
		len++;
		start++;
	}
	return (len);
}

void	token_add_back(t_token **token, t_token *add)
{
	if (!add)
		return ;
	if (!*token)
		*token = add;
	else
	{
		while (*token)
			token = &(*token)->next;
		*token = add;
	}
}

void	free_token(t_token **token)
{
	t_token	*current;

	while (*token)
	{
		current = *token;
		*token = current->next;
		if (current->word)
			free(current->word);
		free(current);
	}
}
