/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:33:48 by wnocchi           #+#    #+#             */
/*   Updated: 2024/05/14 10:54:10 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

int	in_child(t_msh *msh) // enfant qui lis dans un infile
{
	pid_t	c_in;
	pid_t	c_pipe;
	int		pipefd[2];

	c_in = fork();
	if (c_in == 0)
	{
		close(pipefd[0]); // Ferme le côté lecture du pipe (non utilise)
		close(msh->out); // ferme le file de sortie (non utilise)
        dup2(msh->in, STDIN_FILENO); // Lis dans le file a la place de l'entre standard
        dup2(pipefd[1], STDOUT_FILENO); // ecrit dans le pipe au lieu de la sortie standard
        close(pipefd[1]); // ferme le pipe d'ecriture
		close(msh->in); // ferme le file de lecture
        // execve("PATH", char **cmd+args, NULL);
        // perror("");
        return (0);
	}
	else
		return (1);
	c_pipe = fork();
	if(c_pipe == 0)
	{
		close(msh->in); // ferme le(s) fichier(s) in
		close(msh->out); // ferme le(s) fichier(s) out
		dup2(pipefd[0], STDIN_FILENO); // lis dans l'entree du pipe
		// dup2(pipefd[1], STDOUT_FILENO); // ecris dans la sortie du pipe
        close(pipefd[0]); // ferme le pipe d'ecriture
        close(pipefd[1]); // ferme le pipe d'ecriture
	}
	else
		return (1);
	return (0);
}


int	infinite_pipe_child(t_msh *msh)
{
	int	pipefd[msh->nb_cmd];
	int	i;

	i = 0;
	while(i < msh->nb_cmd)
	{
		if(fork() == 0)
		{
			close(msh->in);
			close(msh->out);
		}
	}
}
// int	in_pipe(t_msh *msh)
// {
// 	pid_t	c_pipe;
// 	int		pipefd[2];
	
// 	c_pipe = fork();
// 	if(c_pipe == 0)
// 	{
// 		close(msh->in); // ferme le(s) fichier(s) in
// 		close(msh->out); // ferme le(s) fichier(s) out
// 		dup2(pipefd[0], STDIN_FILENO); // lis dans l'entree du pipe
// 		dup2(pipefd[1], STDOUT_FILENO); // ecris dans la sortie du pipe
//         close(pipefd[0]); // ferme le pipe d'ecriture
//         close(pipefd[1]); // ferme le pipe d'ecriture
// 	}
// }
