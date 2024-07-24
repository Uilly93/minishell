/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:24:11 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/24 08:42:59 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char **all_env(t_env *env)
{
	t_env *current;
	int	i;
	const char **up_env = ft_calloc(sizeof(char *), env_len(env) + 1);

	if(!up_env)
		return (NULL);
	i = 0;
	current = env;
	while(current)
	{
		up_env[i] = ft_strdup(current->full_var);
		if(!up_env)
			return (free_tab((char **)up_env), NULL);
		i++;
		current = current->next;
	}
	return ((char **)up_env);
}

int	update_env(t_env *env)
{
	t_env *current;

	current = env;
	while(current)
	{
		// printf("while");
		if(current->full_env)
			free_tab(current->full_env);
		current->full_env = all_env(current);
		if(!current->full_env)
			return (1);
		current = current->next;
	}
	return (0);
}

int	ft_del_node(t_env **head, char *av)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if(av && ft_strcmp(av, current->key) == 0)
		{
			free(current->value);
			free(current->key);
			free(current->full_var);
			free_tab(current->full_env);
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_env **head, char **av)
{
	int i;

	i = 1;
	if(av[0] && !av[1])
		return (0);
	while(av[i])
	{
		ft_del_node(head, av[i]);
		i++;
	}
	update_env(*head);
	return (0);
}
