/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:47:22 by tchalaou          #+#    #+#             */
/*   Updated: 2024/08/13 13:21:57 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	return (c != ' ' && c != '\t' && c != '\v' && c != '\n');
}

int	word_len(char *line, int start)
{
	int	len;

	len = 0;
	while (line[start] && !ft_strchr(" \t\n<>|'\"", line[start]))
	{
		len++;
		start++;
	}
	return (len);
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

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}
