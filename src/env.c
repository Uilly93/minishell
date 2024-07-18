/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:46:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/18 14:37:22 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int is_equal(char *var)
{
	int		i;
	// int		plus_sign;

	i = 0;
	while (var[i])
	{
		if (var[i] == '+' || var[i] == '=')
		{
			if(var[i] == '+')
				if(var[i + 1] && var[i + 1] != '=')
					return (3);
			if(var[i] == '+' && var[i + 1] && var[i + 1] == '=')
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
	// if(is_equal(var) == 3)
	// 	return (NULL);
	if (!is_equal(var) || is_equal(var) == 3)
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
		return (NULL);
	while (var[i] != '=')
		i++;
	if((size_t)i == ft_strlen(var))
		return (NULL);
	else
		return (ft_substr(var, i + 1, (ft_strlen(var) - i)));
}


int	split_env(t_env *env)
{
	t_env *current;

	current = env;
	while (current)
	{
		// if(current->var)
		// free(current->var);
		current->var = get_var(current->full_var);
		// if (!current->var)
		// 	return (1);
		current->var_name = get_var_name(current->full_var);
		// if (!current->var_name)
		// 	return (1);
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
		if(current->var != NULL)
			ft_printf(fd, "%s=%s\n", current->var_name, current->var);
		current = current->next;
		i++;
	}
	return (0);
}

