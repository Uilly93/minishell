/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:22:27 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/09 11:22:44 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*no_env(char *full_var)
{
	t_env	*tmp;

	tmp = ft_calloc(sizeof(t_env), 1);
		if(!tmp)
			return (NULL);
	tmp->full_var = ft_strdup(full_var);
	return (tmp);
}

void	add_underscore(t_env *env)
{
	t_env	*current;
	t_env	*tmp;
	bool	found;

	found = false;
	current = env;
	while (current)
	{
		if (ft_strcmp(current->full_var, "_=/usr/bin/env") == 0)
			found = true;
		current = current->next;
	}
	if (found == false)
	{
		tmp = no_env("_=/usr/bin/env");
		add_env_node(&env, tmp);
		return ;
	}
}

t_env	*env_into_list(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	env = NULL;
	i = 0;
	if (!envp || !*envp)
	{
		tmp = no_env("_=/usr/bin/env");
		add_env_node(&env, tmp);
	}
	else
	{
		while (envp[i])
		{
			tmp = create_env_node(envp, i);
			add_env_node(&env, tmp);
			i++;
		}
	}
	add_underscore(env);
	update_env(&env);
	split_env(&env);
	return (env);
}

char *join_name_var(t_env *env)
{
	char	*tmp;
	char	*res;

	if (!env->value)
		return (ft_strjoin(env->key, "="));
	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, env->value);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

char **get_env(t_env *env)
{
	int			i;
	const char	**cpy = ft_calloc(sizeof(char *), env_len(env) + 1);
	t_env		*current;

	if (!cpy)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		if (is_equal(current->full_var))
			cpy[i] = join_name_var(current);
		else
			cpy[i] = ft_strdup(current->key);
		if (!cpy[i])
			return (free_tab((char **)cpy), NULL);
		current = current->next;
		i++;
	}
	return ((char **)cpy);
}