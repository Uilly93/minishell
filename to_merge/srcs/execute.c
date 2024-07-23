/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 16:15:11 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/23 15:38:42 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_msh *msh)
{
	t_msh	*current;

	current = msh;
	while (current)
	{
		printf("index: %d\n", current->index);
		if (current->cmd)
		{
			int	i = -1;
			while (current->cmd[++i])
				printf("cmd[%d]: %s\n", i, current->cmd[i]);
		}
		if (current->infile)
			printf("infile: %s\n", current->infile);
		if (current->outfile)
			printf("outfile: %s\n", current->outfile);
		current = current->next;
	}
}
