/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 11:23:43 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/09 12:59:30 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_swap_tab(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	**sort_env(char **tab, t_env *env)
{
	int			i;
	const char	**sorted = ft_calloc(sizeof(char *), env_len(env) + 1);

	if (!sorted)
		return (NULL);
	i = 0;
	while (i < env_len(env) - 1)
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			ft_swap_tab(&tab[i], &tab[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while (tab[i] != NULL)
	{
		sorted[i] = ft_strdup(tab[i]);
		if (!sorted[i])
			return (free_tab((char **)sorted), NULL);
		i++;
	}
	return ((char **)sorted);
}

int	print_line(char *line, int fd)
{
	const char	*value = get_value_env(line);
	const char	*name = get_key_env(line);

	if (fd == -1)
		return (free((void *)name), free((void *)value), perror("msh"), 1);
	if (!name)
		return (free((void *)value), 1);
	if (value)
		ft_printf(fd, "declare -x %s=\"%s\"\n", name, value);
	else
		ft_printf(fd, "declare -x %s\n", name);
	free((void *)name);
	free((void *)value);
	return (0);
}

int	print_export(char **sorted, t_msh *msh)
{
	int			i;
	const int	fd = which_fd(msh);

	if (fd == -1)
		return (perror("msh"), 1);
	i = 0;
	while (sorted[i])
	{
		if (print_line(sorted[i], fd))
			return (1);
		i++;
	}
	return (0);
}
