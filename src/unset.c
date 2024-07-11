/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 09:24:11 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/11 09:37:36 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_unset(t_env *env, char *av)
{
	t_env	*current;

	current = env;
	if(!av)
		return (0);
	while(current)
	{
		if(av && ft_strcmp(av, current->var_name) == 0)
			{
				current->full_var = NULL;
			}
	}
}