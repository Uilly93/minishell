/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 13:51:23 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/24 16:24:16 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_value_parsing(t_env *env, char *key)
{
	t_env	*current;
	int	key_len;

	current = env;
	key_len = ft_strlen(key);
	while (current)
	{
		if (!ft_strncmp(key, current->key, key_len) && !current->key[key_len])
			return (current->value);
		current = current->next;
	}
	return ("");
}

void	fill_value(t_token *token, char *line, int *i)
{
	char	*key;
	char	*value;
	char	*tmp;
	int		k;

	(*i)++;
	key = ft_calloc(sizeof(char), word_len(line, *i) + 1);
	if (!key)
		return ;
	k = 0;
	while (line[*i] && !ft_strchr(" \t\n<>|'\"$", line[*i]))
	{
		key[k++] = line[*i];
		(*i)++;
	}
	key[k] = 0;
	if (!ft_strlen(key))
		value  = ft_strdup("$");
	else
		value = ft_strdup(get_value_parsing(token->env, key));
	free(key);
	if (value)
	{
		tmp = ft_strjoin(token->word, value);
		free(value);
		free(token->word);
		token->word = tmp;
	}
}

void	fill_word(t_token *token, char *line, int *i)
{
	int	j;

	token->id = WORD;
	token->word = ft_calloc(sizeof(char), word_len(line, *i) + 1);
	if (!token->word)
		return ;
	j = 0;
	while (line[*i] && !ft_strchr(" \t\n<>|'\"", line[*i]))
	{
		if (line[*i] == '$')
		{
			fill_value(token, line, i);
			(*i)--;
			return ;
		}
		token->word[j++] = line[*i];
		(*i)++;
	}
	token->word[j] = 0;
	(*i)--;
}

void	fill_quote(t_token *token, char *line, int *i)
{
	int	j;
	int	len;

	token->id = WORD;
	(*i)++;
	j = *i;
	len = 0;
	while (line[j] && line[j++] != '\'')
		len++;
	token->word = ft_calloc(sizeof(char), len + 1);
	if (!token->word)
		return ;
	j = 0;
	while (line[*i] && line[*i] != '\'')
	{
		token->word[j++] = line[*i];
		(*i)++;
	}
	token->word[j] = 0;
	if (line[*i] == '\'')
		(*i)++;
}

void	fill_doublequote(t_token *token, char *line, int *i)
{
	int	j;
	int	len;

	token->id = WORD;
	(*i)++;
	j = *i;
	len = 0;
	while (line[j] && line[j++] != '"')
		len++;
	token->word = ft_calloc(sizeof(char), len + 1);
	if (!token->word)
		return ;
	j = 0;
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$')
		{
			fill_value(token, line, i);
			if (line[*i] == '"')
				(*i)++;
			return ;
		}
		token->word[j++] = line[*i];
		(*i)++;
	}
	token->word[j] = 0;
	if (line[*i] == '"')
		(*i)++;
}

void	fill_token(t_token *token, char *line, int *i)
{
	while (!is_whitespace(line[*i]))
		(*i)++;
	if (!line[*i])
		return ;
	if (line[*i] == '\'')
		fill_quote(token, line, i);
	else if (line[*i] == '"')
		fill_doublequote(token, line, i);
	else if (line[*i] == '<')
		token->id = SMALLER;
	else if (line[*i] == '>')
		token->id = BIGGER;
	else if (line[*i] == '|')
	{
		if((size_t)*i != ft_strlen(line))
			token->id = PIPE;
	}
	else
		fill_word(token, line, i);
}

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
		fill_token(add, line, &i);
		token_add_back(&token, add);
	}
	return (token);
}

/*
int	main()
{
	t_token	*token;
	t_token *start;

	token = lexing(" aa; <bb> | $cc ");
	start = token;
	while (token)
	{
		printf("id: %d\n", token->id);
		if (token->word)
			printf("word: %s\n", token->word);
		token = token->next;
	}
	free_token(&start);
	return (0);
}*/
