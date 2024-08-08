/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:43:11 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/08 13:35:39 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free(void *pointer)
{
	if(pointer)
	{
		free(pointer);
		pointer = NULL;
	}
}

int	get_pwd(char **arg, t_msh *msh)
{
	char		*pwd;
	const int	fd = which_fd(msh);

	if (fd == -1)
		return (perror("msh"), 1);
	if (*arg && ft_strcmp(*arg, "pwd") == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		ft_printf(fd, "%s\n", pwd);
		free(pwd);
		set_excode(&msh->env, 0);
	}
	return (0);
}
