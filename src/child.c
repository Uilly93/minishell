/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:33:48 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/14 14:59:34 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <linux/limits.h>
#include <unistd.h>

int	redirect_fd_read(t_msh *msh, int *pipefd)
{
	// if (msh->outfile != NULL)
	// 	close(msh->out);
	close(pipefd[0]);
	if (/* msh->infile == NULL &&  */msh->index != 1)
	{
		if (dup2(pipefd[1], STDIN_FILENO) == -1)
			return (close(pipefd[1]),/*  close(msh->in),  */1);	
	}
	// else if (msh->infile)
	// {
	// 	if (dup2(msh->in, STDIN_FILENO) == -1)
	// 		return (close(msh->in), close(pipefd[1]), 1);
	// }
	// close(msh->in);
	close(pipefd[1]);
	return (0);
}
int	redirect_fd_write(t_msh *msh, int *pipefd)
{
	// if (msh->infile != NULL)
	// 	close(msh->in);
	close(pipefd[1]);
	printf("adress node %p\n",msh);
	printf("adress next->node %p\n",msh->next);
	if (/* msh->outfile == NULL &&  */msh->next)
	{
		if (dup2(pipefd[0], STDOUT_FILENO) == -1)
			return (close(pipefd[0]),/*  close(msh->out),  */1);
	}
	// else if (msh->outfile)
	// {
	// 	if (dup2(msh->out, STDOUT_FILENO) == -1)
	// 		return (close(msh->out), close(pipefd[0]), 1);
	// }
	close(pipefd[0]);
	// close(msh->out);
	return (0);
}



int	create_child(t_msh *msh, int *pipefd, char **envp, char *av) // enfant qui lis dans un infile
{
	pid_t	child;
	char	*path;

	child = fork();
	if (child == 0)
	{
		path = join_path_access(av, envp);
		redirect_fd_read(msh, pipefd);
		redirect_fd_write(msh, pipefd);
		if(execve(av, msh->cmd, envp) == -1)
			return (free(path), 1);
		free(path);
	}
	return (0);
}

// int	in_pipe(t_msh *msh)
// {
// 	pid_t	c_pipe;
// 	int		pipefd[2];
	
// 	c_pipe = fork();
// 	if (c_pipe == 0)
// 	{
// 		close(msh->in); // ferme le(s) fichier(s) in
// 		close(msh->out); // ferme le(s) fichier(s) out
// 		dup2(pipefd[0], STDIN_FILENO); // lis dans l'entree du pipe
// 		dup2(pipefd[1], STDOUT_FILENO); // ecris dans la sortie du pipe
//         close(pipefd[0]); // ferme le pipe d'ecriture
//         close(pipefd[1]); // ferme le pipe d'ecriture
// 	}
// }
