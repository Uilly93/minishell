/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/12 16:16:39 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

char	*get_home(t_env *env)
{
	char	*res;
	t_env	*current;

	current = env;
	res = NULL;
	while (current)
	{
		if (current->key && ft_strcmp(current->key, "HOME") == 0)
		{
			if (current->value)
				res = ft_strdup(current->value);
			else
				break ;
			if (!res)
				return (NULL);
			return (res);
		}
		current = current->next;
	}
	return (ft_printf(2, "msh: cd: $HOME not set"), NULL);
}

int	update_OLDPWD(char *old_pwd, t_env **env)
{
	t_env	*current;
	t_env	*new_var;
	
	current = *env;

	while(current)
	{
		if(!ft_strcmp(current->key, "OLDPWD"))
		{
			ft_printf(1, "ok\n");
			if(current->value)
				free(current->value);
			free(current->full_var);
			current->value = ft_strdup(old_pwd);
			current->full_var = ft_strjoin("OLDPWD=", old_pwd);
			ft_printf(1, "full =%s\nkey =%s\nvalue =%s\n", current->full_var, current->key, current->value);
			return (update_env(env) ,0);
		}
		current = current->next;
	}
	new_var = ft_calloc(sizeof(t_env), 1);
	if (!new_var)
		return (set_excode(env, 1), 1);
	new_var->full_var = ft_strjoin("OLDPWD=", old_pwd);
	new_var->key = get_key_env("OLDPWD");
	new_var->value = get_value_env(old_pwd);
	ft_printf(1, "full =%s\n key =%s\n value =%s\n", new_var->full_var, new_var->key, new_var->value);
	return (add_env_node(env, new_var), update_env(env), 0);
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
	(void)arg;
	if (!path)
		return (1);
	if (!*path)
		return (ft_printf(1, "msh: cd: $HOME not set\n"), free(path), 1);
	// if (arg && *arg != 0)
	// 	return (ft_printf(1, "msh: cd: too many arguments\n"), free(path), 1);
	if (chdir(path) == -1)
		return (perror("msh: cd"), free(path), 1);
	free(path);
	return (0);
}

int	ft_cd(char **arg, t_env **env)
{
	const char	*pwd = getcwd(NULL, 0);
	char		*path;

	path = NULL;
	update_OLDPWD((char *)pwd, env);
	if (*arg && ft_strcmp(*arg++, "cd") == 0)
	{
		if (*arg && chdir(*arg) != -1)
			return (free((char *)pwd), set_excode(env, 0), 0);
		if (!pwd)
			return (set_excode(env, 1), 1);
		if (*arg && **arg)
			path = join_path(*arg++, (char *)pwd);
		else
			path = get_home(*env);
		ft_printf(1, "path=%s\n",path);
		free((char *)pwd);
		if (!path)
			return (set_excode(env, 1), 1);
		set_excode(env, err_and_chdir(path, arg));
	}
	return (0);
}
