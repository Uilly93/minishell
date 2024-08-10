/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:00:01 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/09 13:03:45 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_vars(char *av, char *value)
{
	char	*add;
	char	*tmp;

	add = get_value_env(av);
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

bool	update_it(char *av, t_env *current, const char *v, const char *v_name)
{
	free(current->full_var);
	current->full_var = ft_strdup(av);
	current->value = join_vars(av, current->value);
	free((void *)v_name);
	free((void *)v);
	return (true);
}
