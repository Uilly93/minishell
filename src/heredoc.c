/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:45:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/05 16:40:51 by wnocchi          ###   ########.fr       */
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
			if (av[i + 1] != NULL && av[i + 2] && ft_strcmp(av[i + 2], ">") == 0)
			{
				if(av[i + 3] != NULL)
					msh->out = open(av[i + 3], O_CREAT | O_WRONLY | O_TRUNC, 0644);
			}
			else if (av[i + 1] != NULL && av[i + 2] && ft_strcmp(av[i + 2], ">>") == 0)
			{
				if(av[i + 3] != NULL)
				msh->out = open(av[i + 3], O_CREAT | O_WRONLY | O_APPEND, 0644);
			}
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
		line = readline(MAGENTA"msh_heredoc> "RESET);
		while (line)
		{
			if (!line || ft_strcmp(line, msh->hlimit) == 0)
			{
				free(line);
				free(msh->hlimit);
				return ;
			}
			if(msh->out == -1)
				ft_putendl_fd(line, msh->out);
			free(line);
			line = readline(MAGENTA"msh_heredoc> "RESET);
		}
		free(line);
		free(msh->hlimit);
	}
}
