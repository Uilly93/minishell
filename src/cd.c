/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/27 10:49:29 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *get_home(char **envp)
{
	int i;
	char **tab;
	char *res;
	
	i = 0;
	while(envp[i])
	{
		if(ft_strncmp(envp[i], "HOME=", 5) == 0)
		{
			tab = ft_split(envp[i], '=');
			if(!tab)
				return (NULL);
			res = ft_strdup(tab[1]);
			if(!res)
				return (free_tab(tab), NULL);
			free_tab(tab);
			return (res);
		}
		i++;
	}
	return (NULL);
}

void ft_err(char *error)
{
	write(2, (BOLD_RED), ft_strlen(BOLD_RED));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	write(2, (RESET), ft_strlen(RESET));

}

char *join_path(char *arg, char *pwd)
{
	char *tmp;
	char *path;
	
	tmp = ft_strjoin(pwd, "/");
	// free(pwd);
	if (!tmp)
		return (free(pwd), NULL);
	path = ft_strjoin(tmp, arg);
	free(tmp);
	if (!path)
		return (free(pwd), free(path), NULL);
	return (path);
}

int	err_and_chdir(char *path, char *arg)
{

	if (!path)
		return (1);
	if (arg)
		return (ft_err("msh: cd: too many arguments"), free(path), 1);
	if (chdir(path) == -1)
		return (ft_err("msh: cd: No such file or directory"), free(path), 1);
	free(path);
	return (0);
}

int	ft_cd(char **arg, char **envp)
{
	char	*pwd;
	char	*path;

	if (*arg && ft_strcmp(*arg++, "cd") == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		if(*arg)
			path = join_path(*arg++, pwd);
		else
			path = get_home(envp);
		free(pwd);
		if (!path)
			return (1);
		err_and_chdir(path, *arg);
	}
	return (0);
}
