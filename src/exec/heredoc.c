/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:45:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/06 17:49:41 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>
#include <unistd.h>

int init_heredoc(t_msh *msh, const char	*cpy)
{
	g_last_sig = 0;
	free(msh->infile);
	msh->infile = ft_strjoin("/tmp/", cpy);
	if (!msh->infile)
		return(free((void *)cpy), 1);
	msh->in = open(msh->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (msh->in == -1)
		return (perror("msh"), free((void *)cpy), 1);
	if (!msh->cmd)
		unlink(msh->infile);
	return (0);
}

int	here_doc(t_msh *msh)
{
	char		*line;
	const char	*cpy = ft_strdup(msh->infile);

	if(!cpy || init_heredoc(msh, cpy))
		return(1);
	line = readline(MAGENTA"msh_heredoc> "RESET);
	while (line)
	{
		if (!line || ft_strcmp(line, (char *)cpy) == 0 || g_last_sig == SIGINT)
		{
			free((void *)cpy);
			free(line);
			if(g_last_sig == SIGINT)
			{
				unlink(msh->infile);
				return (SIGINT);
			}
			return (0);
		}
		ft_putendl_fd(line, msh->in);
		free(line);
		line = readline(MAGENTA"msh_heredoc> "RESET);
	}
	free(line);
	return (0);
}
