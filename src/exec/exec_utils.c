/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:22:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/10 13:08:24 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_global(t_env **env)
{
	if (g_last_sig == SIGQUIT)
		set_excode(env, 131);
	if (g_last_sig == SIGINT)
		set_excode(env, 130);
	g_last_sig = 0;
	init_sigint();
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

int	check_exec(char *cmd, t_msh *msh, t_env **env)
{
	if (ft_strlen(cmd) >= 2 && ft_strncmp(cmd, "./", 2) == 0)
	{
		if (access(cmd, F_OK) != 0)
		{
			ft_printf(2, "msh: %s: No such file or directory\n", cmd);
			free_env(env);
			free_lst(msh);
			exit(127);
		}
		else if (access(cmd, X_OK) != 0)
		{
			if (errno == EISDIR)
				ft_printf(2, "msh: %s: Is a directory\n", cmd);
			else
				ft_printf(2, "msh: %s: Permission denied\n", cmd);
			free_env(env);
			free_lst(msh);
			exit(126);
		}
	}
	return (0);
}

char	**get_path(t_env *env)
{
	t_env	*current;

	current = env;
	if (!current)
		return (NULL);
	while (current)
	{
		if (ft_strcmp("PATH", current->key) == 0)
			return (ft_split(current->value, ':'));
		else
			current = current->next;
	}
	return (NULL);
}

char	*join_path_access(char *av, t_env *env)
{
	int		i;
	char	**s;
	char	*res;

	i = -1;
	if (access(av, X_OK) == 0)
		return (ft_strdup(av));
	s = get_path(env);
	if (!s)
		return (NULL);
	while (s[++i])
	{
		res = ft_strjoin(s[i], "/");
		if (!res)
			return (free_tab(s), NULL);
		res = join_free(res, av);
		if (!res)
			return (free_tab(s), NULL);
		if (access(res, X_OK) == 0)
			return (free_tab(s), res);
		free(res);
	}
	free_tab(s);
	return (NULL);
}
