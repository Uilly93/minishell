/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:07:38 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/23 16:20:12 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *join_vars(char *av, char *value)
{
	char	*add;
	char	*tmp;

	add = get_value(av);
	if (!value)
		return (add);
	tmp = ft_strdup(value);
	if (!tmp)
		return (free(add), NULL);
	free(value);
	value = ft_strjoin(tmp, add);
	free(add);
	free(tmp);
	if (!value)
		return (NULL);
	return (value);
}

bool	update(char *av, t_env *current, const char *value, const char *key)
{
		free(current->full_var);
		current->full_var = ft_strdup(av);
		current->value = join_vars(av, current->value);
		free((void*)key);
		free((void*)value);
		return (true);
}
