/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:45:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/03 13:25:47 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_heredoc(t_msh *msh, char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_strcmp(av[i], "<<") == 0 && av[i + 1])
		{
			msh->hlimit = ft_strdup(av[i + 1]);
			if (!msh->hlimit)
				return(1);
			if (av[i + 1] != NULL && ft_strcmp(av[i + 2], ">") == 0)
				msh->out = open(av[i + 3], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (av[i + 1] != NULL && ft_strcmp(av[i + 2], ">>") == 0)
				msh->out = open(av[i + 3], O_CREAT | O_WRONLY | O_APPEND, 0644);
			return (1);
		}
		else
			i++;
	}
	return (0);
}

void	here_doc(t_msh *msh, char **av)
{
	char	*line;

	if (*av && check_heredoc(msh, av))
	{
		line = readline("msh_heredoc> ");
		while (line)
		{
			if (!line || ft_strcmp(line, msh->hlimit) == 0)
			{
				free(line);
				free(msh->hlimit);
				return ;
			}
			ft_putendl_fd(line, msh->out);
			free(line);
			line = readline("msh_heredoc> ");
		}
		free(line);
		free(msh->hlimit);
	}
}
