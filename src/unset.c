/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:24:11 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/12 15:07:42 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_del_node(t_env **head, char **av)
{
	t_env	*current;
	t_env	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if(av[1] && ft_strcmp(av[1], current->var_name) == 0)
		{
			free(current->var);
			free(current->var_name);
			free(current->full_var);
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
		if(ft_del_node(head, av))
			return (0);
	return (0);
}
