/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 09:43:11 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/03 13:26:29 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_pwd(char **arg)
{
	char *pwd;

	// arg++;
	if (*arg && ft_strcmp(*arg, "pwd") == 0)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (1);
		printf("%s\n", pwd);
		free(pwd);
	}
	return (0);
}