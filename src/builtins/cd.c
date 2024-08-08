/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/08 15:30:42 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

char	*get_home(t_env *env)
{
	char	*res;
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "HOME") == 0)
		{
			res = ft_strdup(current->value);
			if (!res)
				return (NULL);
			return (res);
		}
		current = current->next;
	}
	return (ft_err("msh: cd: $HOME not set"), NULL);
}

void	ft_err(char *error)
{
	ft_printf(2, "%s\n", error);
}

char	*join_path(char *arg, char *pwd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(pwd, "/");
	if (!tmp)
		return (free(pwd), NULL);
	path = ft_strjoin(tmp, arg);
	free(tmp);
	if (!path)
		return (free(pwd), free(path), NULL);
	return (path);
}

int	err_and_chdir(char *path, char **arg)
{
	if (!path)
		return (1);
	if (!*path)
		return (ft_err("msh: cd: $HOME not set"), free(path), 1);
	if (arg && arg[0])
		return (ft_err("msh: cd: too many arguments"), free(path), 1);
	if (chdir(path) == -1)
		return (ft_err("msh: cd: No such file or directory"), free(path), 1);
	free(path);
	return (0);
}

int	ft_cd(char **arg, t_env **env)
{
	char	*pwd;
	char	*path;

	path = NULL;
	if (*arg && ft_strcmp(*arg++, "cd") == 0)
	{
		if(chdir(*arg) != -1)
			return (set_excode(env, 0), 0);
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (set_excode(env, 1), 1);
		if (*arg && **arg)
			path = join_path(*arg++, pwd);
		else
			path = get_home(*env);
		free(pwd);
		if (!path)
			return (set_excode(env, 1), 1);
		set_excode(env, err_and_chdir(path, arg));
	}
	return (0);
}
