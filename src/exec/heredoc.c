/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:45:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/05 08:49:21 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	here_doc(t_msh *msh)
{
	char		*line;
	const char	*cpy = ft_strdup(msh->infile);

	free(msh->infile);
	msh->infile = ft_strjoin("/tmp/", cpy);
	msh->in = open(msh->infile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (msh->in == -1)
		return (perror("msh"), free((void *)cpy), 1);
	if (!msh->cmd)
		unlink(msh->infile);
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
