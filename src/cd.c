/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 15:16:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/05/27 10:15:32 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>
#include <unistd.h>

char	*join_path(char *pwd, char *arg)
{
	char	*res;
	char	*buffer;

	buffer = join_free(pwd, "/");
	if (!buffer)
		return (NULL);
	res = join_free(buffer, arg);
	if (!res)
		return (NULL);
	return (res);
}

int	ft_cd(char **arg)
{
	char	*pwd;
	char	*path;

	arg++; // skip le ./minishell (pour les tests)
	if(ft_strcmp(*arg, "cd") == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		path = join_path(pwd, *arg);
		if (!path)
			return (1);
		if (chdir(path) == -1)
		{
			perror("minishell: cd ");
			free(path);
			return (1);
		}
		free(path);
	}
	return (0);
}