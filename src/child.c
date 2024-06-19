/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:33:48 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/19 19:33:05 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <linux/limits.h>
#include <unistd.h>

int	redirect_fd(t_msh *msh, int *pipefd)
{
	// (void)msh;
	printf("pipe0 = %d\n", pipefd[0]);
	printf("pipe1 = %d\n", pipefd[1]);
	if (msh->index != 1)
	{
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			return (close_fds(pipefd, msh),/*  close(msh->in),  */1);	
	}
	if (msh->next != NULL)
	{
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			return (close_fds(pipefd, msh),/*  close(msh->out),  */1);
	}
	// if (msh->in != -1)
	// {
	// 	if(dup2(msh->in, pipefd[0]) == -1)
	// 		return (close_fds(pipefd, msh),/*  close(msh->out),  */1);
	// }
	return (0);
}
int	redirect_fd_write(t_msh *msh, int *pipefd)
{
	if (/* msh->outfile == NULL &&  */msh->next)
	{
		// close(pipefd[1]);
		// printf("test2");
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			printf("dup 2 failed write");
			return (close(pipefd[0]),/*  close(msh->out),  */1);
		}
		// close(pipefd[0]);
	}
	// else if (msh->outfile)
	// {
	// 	if (dup2(msh->out, STDOUT_FILENO) == -1)
	// 		return (close(msh->out), close(pipefd[0]), 1);
	// }
	// close(msh->out);
	return (0);
}