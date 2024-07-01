/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:45:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/01 15:34:07 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	check_heredoc(t_msh *msh, char **av)
{
	char *filename;
	char *index;
	
		if (ft_strcmp(av[0], "<<") == 0 && av[1])
		{
			index = ft_itoa(msh->index);
			if(!index)
				return (1);
			filename = ft_strjoin("/tmp/heredoc_", index);
			free(index);
			if(!filename)
				return (1);
			unlink(filename);
			msh->hlimit = ft_strdup(av[1]);
			if (!msh->hlimit)
				return(free(filename),1);
			msh->in = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			unlink(filename);
			free(filename);
			if(msh->in == -1)
				return (/* free(msh->hlimit),  */perror("msh"), 1);
		}
	return (0);
}

void	here_doc(t_msh *msh, char **av)
{
	char	*line;

	if (*av && check_heredoc(msh, av) == 0)
	{
		line = readline(MAGENTA"msh_heredoc> "RESET);
		while (line)
		{
			if (!line || ft_strcmp(line, msh->hlimit) == 0)
			{
				// if(msh->in != -1)
				// 	close(msh->in);
				free(line);
				// free(msh->hlimit);
				return ;
			}
				ft_putendl_fd(line, msh->in);
			free(line);
			line = readline(MAGENTA"msh_heredoc> "RESET);
		}
		free(line);
		// free(msh->hlimit);
	}
}
