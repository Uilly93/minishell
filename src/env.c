/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:46:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/16 10:38:56 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int is_equal(char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '+' || var[i] == '=')
		{
			if(var[i] == '+' && var[i+1] == '=')
				return(2);
			return (1);	
		}
		i++;
	}
	return (0);
}

char *get_var_name(char *var)
{
	int	i;
	
	i = 0;
	if (!is_equal(var))
		return (ft_strdup(var));
	while (var[i] != '=')
		i++;
	if(var[i - 1] == '+')
		i--;
	return (ft_substr(var, 0, i));
}

char *get_var(char *var)
{
	int		i;

	i = 0;
	if (!is_equal(var))
		return (ft_strdup(""));
	while (var[i] != '=')
		i++;
	return (ft_substr(var, i + 1, (ft_strlen(var) - i)));
}


int	split_env(t_env *env)
{
	t_env *current;

	current = env;
	while (current)
	{
		current->var = get_var(current->full_var);
		if (!current->var)
			return (1);
		current->var_name = get_var_name(current->full_var);
		if (!current->var)
			return (1);
		current = current->next;
	}
	return (0);
}

int ft_env(t_env *env, t_msh * msh)
{
	t_env *current;
	int i = 0;
	const int	fd = which_fd(msh);

	if(fd == -1)
		return (perror("msh"), 1);
	current = env;
	while(current)
	{
		if((is_equal(current->full_var) && !*current->var) || *current->var)
			ft_printf(fd, "%s=%s\n", current->var_name, current->var);
		current = current->next;
		i++;
	}
	return (0);
}

