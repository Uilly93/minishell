/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:45:46 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/15 13:58:46 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_heredoc(t_msh *msh, const char	*cpy)
{
	g_last_sig = 0;
	free(msh->infile);
	msh->infile = ft_strjoin("/tmp/", cpy);
	if (!msh->infile)
		return (free((void *)cpy), 1);
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
	char		*exp_line;
	const char	*cpy = ft_strdup(msh->infile);

	if (!cpy || init_heredoc(msh, cpy))
		return (set_excode(&msh->env, 1), 1);
	while (1)
	{
		line = readline(MAGENTA"msh_heredoc> "RESET);
		if (!line || !ft_strcmp(line, (char *)cpy) || g_last_sig == SIGINT)
		{
			free((void *)cpy);
			if (g_last_sig == SIGINT)
				return (free(line), unlink(msh->infile), SIGINT);
			return (free(line), 0);
		}
		exp_line = expand_variable(&msh->env, line);
		ft_putendl_fd(exp_line, msh->in);
		free(exp_line);
		free(line);
	}
}
