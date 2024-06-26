/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/26 17:16:28 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

char *get_user(char **envp)
{
	int i;
	char **tab;
	char *res;
	
	i = 0;
	while(envp[i])
	{
		if(ft_strncmp(envp[i], "HOME=", 5))
		{
			tab = ft_split(envp[i], '=');
			if(!tab)
				return (NULL);
			res = ft_strjoin("/home/", tab[1]);
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

int	no_args(char **arg, char **envp)
{
	char *usr;
	char *res;
	
	if (*arg == NULL)
	{
		usr = get_user(envp);
		res = ft_strjoin("/home/", usr);
		if(!res)
			return (free(usr), 1);
		free(usr);
		if(chdir(res) == -1)
			return (perror("minishell: cd"), free(res), 1);
		free(res);
		return (0);
	}
	return (0);
}

char *add_path(char **arg, char *pwd)
{
	char *tmp;

	tmp = ft_strjoin(pwd, "/"); // protect
	if(!tmp)
		return (NULL);
	tmp = join_free(tmp, *arg++); //protect
	if(!tmp)
		return (NULL);
	return(tmp);
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
		if (*arg == NULL)
			path = get_user(envp); //protect
		else
		{
			path = ft_strjoin(pwd, "/"); // protect
			path = join_free(path, *arg++); //protect
		}
		free(pwd);
		if (!path)
			return (1);
		if (*arg)
			return (ft_err("minishell: cd: too many arguments"), free(path), 1);
		if (chdir(path) == -1)
			return (perror("minishell: cd"), free(path), 1);
		free(path);
	}
	return (0);
}
