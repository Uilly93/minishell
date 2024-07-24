/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:00:34 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/24 08:42:51 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <limits.h>

bool	only_digit_string(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' && s[i] <= '9')
			i++;
		else
			return (true);
	}
	return (false);
}

bool	overflow(char *s)
{
	int		i;
	int		sign;
	__int128	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ' || s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		sign *= -1;
		i++;
	}
	if (only_digit_string(s + i))
		return (true);
	while (s[i] >= '0' && s[i] <= '9')
	{
		nbr = (nbr * 10 + s[i++] - '0');
		if (nbr * sign > LONG_MAX || nbr * sign < LONG_MIN)
			return (true);
	}
	return (false);
}

long ft_atol(char *s)
{
	int		i;
	int		sign;
	long	nbr;

	i = 0;
	sign = 1;
	nbr = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ' || s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		nbr = (nbr * 10 + s[i++] - '0');
	return (nbr);
}

int ft_exit(t_msh *msh, t_env *env)
{
	long exit_code;
	
	if(ft_lstlen(msh) >= 2)
		return (1);
	if (msh->cmd[1] && overflow(msh->cmd[1]))
	{
		ft_printf(2, "exit\n");
		ft_printf(2, BOLD_RED"msh: exit: %s: numeric argument required\n"RESET,
		msh->cmd[1]);
		return (free_lst(msh), free_env(env), exit(2), 0);
	}
	if (!msh->cmd[1])
		return (ft_printf(2, "exit\n"), free_env(env), free_lst(msh),
				exit(0), 0);
	if(msh->cmd[1] && msh->cmd[2] != NULL)
		return (ft_err("msh: exit: too many arguments"), 1);
	exit_code = ft_atol(msh->cmd[1]);
	if (exit_code <= 255)
		return (ft_printf(2, "exit\n"), free_env(env), free_lst(msh),
				exit(exit_code), 0);
	else
		return (ft_printf(2, "exit\n"), free_env(env), free_lst(msh),
				exit(exit_code % 256), 0);
	return (0);
}
