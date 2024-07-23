/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 08:53:08 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/23 15:23:22 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	const char	*var = get_var(line);
	const char	*key = get_key(line);

	if (fd == -1)
		return (free((void *)key), free((void *)var), perror("msh"), 1);
	if (!key)
		return (free((void *)var), 1);
	if (var)
		ft_printf(fd, "define -x %s=\"%s\"\n", key, var);
	else
		ft_printf(fd, "define -x %s\n", key);
	free((void *)key);
	free((void *)var);
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


char *join_vars(char *av, char *var)
{
	char	*add;
	char	*tmp;

	add = get_var(av);
	if (!var)
		return (add);
	tmp = ft_strdup(var);
	if (!tmp)
		return (free(add), NULL);
	free(var);
	var = ft_strjoin(tmp, add);
	free(add);
	free(tmp);
	if (!var)
		return (NULL);
	return (var);
}
