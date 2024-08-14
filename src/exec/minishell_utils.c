/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:26:23 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/14 14:12:26 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

t_msh	*ft_lastnode(t_msh *lst)
{
	t_msh	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

int	ft_lstlen(t_msh *msh)
{
	t_msh	*current;
	int		i;

	if (!msh)
		return (0);
	current = ft_lastnode(msh);
	i = 0;
	while (current)
	{
		current = current->prev;
		i++;
	}
	return (i);
}

void	free_lst(t_msh *msh)
{
	t_msh	*current;
	t_msh	*next;

	current = ft_lastnode(msh);
	while (current)
	{
		close_files(current);
		if (current->outfile)
			free(current->outfile);
		if (current->infile)
			free(current->infile);
		free_tab(current->cmd);
		next = current;
		current = current->prev;
		free(next);
	}
}

void	wait_pids(t_env **env)
{
	int	w_pid;
	int	status;

	status = 0;
	while (1)
	{
		w_pid = wait(&status);
		if (w_pid < 0)
		{
			if (errno == ECHILD)
				return ;
			set_excode(env, 1);
		}
		if (WIFEXITED(status))
			set_excode(env, WEXITSTATUS(status));
	}
}

void	set_excode(t_env **env, int code)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		current->ex_code = code;
		current = current->next;
	}
}
