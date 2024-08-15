/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 10:41:41 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/15 15:52:01 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_getenv(t_env **env, char *key)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static char	*append_char(char *str, char c)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = ft_calloc(sizeof(char), len + 2);
	if (!new_str)
		return (NULL);
	ft_strcpy(new_str, str);
	new_str[len] = c;
	free(str);
	return (new_str);
}

static char	*handle_variable_expansion(char *expanded, char *var_value)
{
	char	*temp;

	temp = expanded;
	expanded = ft_calloc(sizeof(char), ft_strlen(expanded)
			+ ft_strlen(var_value) + 1);
	if (!expanded)
		return (NULL);
	ft_strcpy(expanded, temp);
	ft_strcat(expanded, var_value);
	free(temp);
	return (expanded);
}

static char	*handle_expansion(t_env **env, char *expanded, char *line, int *i)
{
	char	*var_name;
	char	*var_value;
	int		start;

	start = ++(*i);
	while (line[*i] && (line[*i] == '_' || ft_isalnum(line[*i])))
		(*i)++;
	var_name = ft_strndup(&line[start], *i - start);
	if (!var_name)
		return (NULL);
	var_value = ft_getenv(env, var_name);
	free(var_name);
	if (var_value)
		expanded = handle_variable_expansion(expanded, var_value);
	return (expanded);
}

char	*expand_variable(t_env **env, char *line)
{
	char	*expanded;
	int		i;

	expanded = ft_strdup("");
	if (!expanded)
		return (NULL);
	i = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1]
			&& (line[i + 1] == '_' || ft_isalnum(line[i + 1])))
		{
			expanded = handle_expansion(env, expanded, line, &i);
			if (!expanded)
				return (NULL);
		}
		else
		{
			expanded = append_char(expanded, line[i]);
			if (!expanded)
				return (NULL);
			i++;
		}
	}
	return (expanded);
}
