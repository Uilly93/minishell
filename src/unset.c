/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:24:11 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/12 11:19:10 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_env *env, char **av)
{
	t_env	*current;

	current = env;
	if(av[0] && !av[1])
		return (1);
	while(current)
	{
		if(av[1] && ft_strcmp(av[1], current->var_name) == 0)
			current->set = false;
		current = current->next;
	}
	return (0);
}