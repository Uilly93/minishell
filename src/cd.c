/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/06 15:05:24 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// char	*join_path(char *pwd, char *arg)
// {
// 	char	*res;
// 	char	*buffer;

// 	buffer = join_free(pwd, "/");
// 	if (!buffer)
// 		return (NULL);
// 	res = join_free(buffer, arg);
// 	if (!res)
// 		return (NULL);
// 	return (res);
// }
void ft_err(char *error)
{
	printf(RED);
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	printf(RESET);
}

int	ft_cd(char **arg)
{
	char	*pwd;
	char	*path;

	if(*arg && ft_strcmp(*arg++, "cd") == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		if(*arg == NULL)
			path = ft_strdup("/home/wnocchi"); // need env to fix
		else
		{
			path = ft_strjoin(pwd, "/");
			path = join_free(path, *arg++);
		}
		free(pwd);
		if (!path)
			return (1);
		if(*arg)
			return (ft_err("minishell: cd: too many arguments"), free(path), 1);
		if (chdir(path) == -1)
			return (perror("minishell: cd"), free(path), 1);
		free(path);
	}
	return (0);
}

// write(2, "msh: cd:too many arguments\n", 27)
