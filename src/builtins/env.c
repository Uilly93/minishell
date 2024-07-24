/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:46:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/24 14:06:06 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

int	is_equal(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '+' || value[i] == '=')
		{
			if (value[i] == '+')
				if (value[i + 1] && value[i + 1] != '=')
					return (3);
			if (value[i] == '+' && value[i + 1] && value[i + 1] == '=')
				return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_key_env(char *value)
{
	int	i;

	i = 0;
	if (!is_equal(value) || is_equal(value) == 3)
		return (ft_strdup(value));
	while ((size_t)i < ft_strlen(value))
	{
		if (value[i] == '=')
		{
			if (value[i - 1] == '+')
				i--;
			return (ft_substr(value, 0, i));
		}
		i++;
	}
	return (ft_strdup(value));
}

char	*get_value_env(char *value)
{
	int		i;

	i = 0;
	if (!is_equal(value))
		return (NULL);
	while (value[i] != '=')
		i++;
	if ((size_t)i == ft_strlen(value))
		return (NULL);
	else
		return (ft_substr(value, i + 1, (ft_strlen(value) - i)));
}

int	split_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		current->value = get_value_env(current->full_var);
		current->key = get_key_env(current->full_var);
		current = current->next;
	}
	return (0);
}

int	ft_env(t_env *env, t_msh *msh)
{
	t_env		*current;
	int			i;
	const int	fd = which_fd(msh);

	i = 0;
	if (fd == -1)
		return (perror("msh"), 1);
	current = env;
	while (current)
	{
		if (current->value != NULL)
			ft_printf(fd, "%s=%s\n", current->key, current->value);
		current = current->next;
		i++;
	}
	return (0);
}
