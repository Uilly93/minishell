/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:45:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/31 14:12:54 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

// int heredoc_signal_handler(int sig) {
//     if (sig == SIGINT) {
//         printf("\nExiting heredoc mode.\n");
//         return (1); // Quitte le mode heredoc
//     }
// 	return (0);
// }

int	check_heredoc(t_msh *msh, char **av)
{
	(void)av;
	// char *filename;
	// char *index;
	
		if (msh->here_doc != -1)
		{
			
			// index = ft_itoa(msh->index);
			// if(!index)
				// return (1);
			// filename = ft_strjoin("/tmp/heredoc_", index);
			// free(index);
			// if(!filename)
			// 	return (1);
			// unlink(filename);
			// msh->hlimit = ft_strdup(av[1]);
			// if (!msh->hlimit)
			// 	return(1);
			// unlink(filename);
			// free(filename);
		}
	return (0);
}

int	here_doc(t_msh *msh)
{
	char		*line;
	const char	*cpy = ft_strdup(msh->infile);
	
	if (msh->here_doc == 0)
		return (0);
	free(msh->infile);
	msh->infile = ft_strjoin("/tmp/", cpy);
	msh->in = open(msh->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(msh->in == -1)
		return (perror("msh"), 1);
	line = readline(MAGENTA"msh_heredoc> "RESET);
	while (line)
	{
		if (!line || ft_strcmp(line, (char *)cpy) == 0)
		{
			free((void *)cpy);
			free(line);
			return (0);
		}
		ft_putendl_fd(line, msh->in);
		free(line);
		line = readline(MAGENTA"msh_heredoc> "RESET);
	}
	free(line);
	return (0);
}
