/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:43:11 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/24 08:42:56 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	get_pwd(char **arg, t_msh *msh)
{
	char *pwd;
	const int	fd = which_fd(msh);

	if(fd == -1)
		return (perror("msh"), 1);
	if (*arg && ft_strcmp(*arg, "pwd") == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		ft_printf(fd,"%s\n", pwd);
		if(msh->out != -1)
			close(msh->out);
		free(pwd);
	}
	return (0);
}
