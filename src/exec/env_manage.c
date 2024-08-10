/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:20:18 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/09 11:20:54 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_env(t_env **env)
{
	t_env	*current;
	t_env	*prev;

	current = *env;
	while (current)
	{
		prev = current;
		free(current->value);
		free(current->full_var);
		free(current->key);
		free_tab(current->full_env);
		current = current->next;
		free(prev);
	}
	free(env);
	return (0);
}

int	env_len(t_env *env)
{
	int		i;
	t_env	*current;

	current = env;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

t_env	*ft_envlastnode(t_env *lst)
{
	t_env	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_env_node(t_env **lst, t_env *add)
{
	if (!lst || !add)
		return ;
	if (!*lst)
		*lst = add;
	else
		ft_envlastnode(*lst)->next = add;
}

t_env	*create_env_node(char **envp, int i)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->full_var = ft_strdup(envp[i]);
	if (!env->full_var)
		return (NULL);
	return (env);
}
