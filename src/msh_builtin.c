/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 09:16:26 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/04 10:37:52 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (ft_split(envp[i], ':'));
		else
			i++;
	}
	return (NULL);
}

char	*join_path_access(char *av, char **envp)
{
	int		i;
	char	**s;
	char	*res;

	i = 0;
	res = NULL;
	s = get_path(envp);
	if (!s)
		return (write(2, "Error: no environment\n", 22), NULL);
	while (s[i])
	{
		res = ft_strcat_malloc(s[i], "/");
		if (!res)
			return (NULL);
		res = join_free(res, av);
		if (!res)
			return (NULL);
		if (access(res, X_OK) == 0)
			return (free_tab(s), res);
		free(res);
		i++;
	}
	free_tab(s);
	return (NULL);
}

int is_it_builtin(char **prompt, t_msh *msh, char **envp)
{
	if(ft_strcmp(*prompt, "<<") == 0)
	{
		here_doc(msh, prompt);
		return (1);
	}
	if(ft_strcmp(*prompt, "echo") == 0)
	{
		ft_echo(prompt);
		return (1);
	}
	if(ft_strcmp(*prompt, "cd") == 0)
	{
		ft_cd(prompt);
		return (1);
	}
	if(ft_strcmp(*prompt, "pwd") == 0)
	{
		get_pwd(prompt);
		return (1);
	}
	else
		execve(join_path_access(*prompt, envp), prompt, envp);
}
