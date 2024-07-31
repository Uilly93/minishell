/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:01:56 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/31 15:00:52 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	which_fd(t_msh *msh)
{
	if (msh->outfile != NULL)
	{
		msh->out = open(msh->outfile, get_flags(msh), 0644);
		return (msh->out);
	}
	else if (msh->next == NULL)
		return (1);
	else if (msh->pipefd[1] != -1)
		return (msh->pipefd[1]);
	else
		return (1);
}

static int	handle_flag(char **prompt, int i)
{
	int	j;

	j = 1;
	while (prompt[i][j])
	{
		if (prompt[i][j] != 'n')
			return (0);
		j++;
	}
	return (1);
}

void	print_args(t_msh *msh, int i, bool new_line)
{
	const int	fd = which_fd(msh);
	int			j;

	j = 1;
	if (fd == -1)
	{
		perror("msh");
		return ;
	}
	if (msh->cmd[i] == NULL)
		return ;
	while (msh->cmd[j++] && msh->cmd[i] != NULL)
	{
		if (msh->cmd[i + 1] == NULL)
			ft_printf(fd, "%s", msh->cmd[i++]);
		else
			ft_printf(fd, "%s ", msh->cmd[i++]);
	}
	if (new_line == true)
		ft_printf(fd, "\n");
	close_files(msh);
}

void	ft_echo(t_msh *msh)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = true;
	if (msh->cmd[0] && ft_strcmp(msh->cmd[i++], "echo") == 0)
	{
		if (msh->cmd[i] == NULL)
			return (ft_printf(which_fd(msh), "\n"), (void) NULL);
		if (msh->cmd[i][0] != '\0' && ft_strncmp(msh->cmd[i], "-n", 2) == 0)
		{
			while (ft_strncmp(msh->cmd[i], "-n", 2) == 0)
			{
				if (handle_flag(msh->cmd, i) == 0)
					break ;
				new_line = false;
				i++;
				if (msh->cmd[i] == NULL)
					return ;
			}
		}
		print_args(msh, i, new_line);
	}
}
