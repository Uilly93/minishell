/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 10:33:48 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/21 16:47:03 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <linux/limits.h>
#include <unistd.h>

int	redirect_fd(t_msh *msh)
{
	if (msh->index != 1)
	{
		if (dup2(msh->prev->pipefd[0], STDIN_FILENO) == -1)
			return (close_fds(msh),/*  close(msh->in),  */1);	
	}
	if (msh->next != NULL)
	{
		if (dup2(msh->pipefd[1], STDOUT_FILENO) == -1)
			return (close_fds(msh),/*  close(msh->out),  */1);
	}
	// if (msh->in != -1)
	// {
	// 	if(dup2(msh->in, pipefd[0]) == -1)
	// 		return (close_fds(pipefd, msh),/*  close(msh->out),  */1);
	// }
	return (0);
}
