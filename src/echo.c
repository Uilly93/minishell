/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 09:01:56 by wnocchi           #+#    #+#             */
/*   Updated: 2024/05/22 17:18:04 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// #include <string.h>

static int handle_flag(char **prompt, int i, int j)
{
	while(prompt[i][j])
	{
		if(prompt[i][j] != 'n')
			return (0);
		j++;
	}
		return (1);
}

void print_args(char **prompt, int j, int i, bool new_line)
{
	if(prompt[i] == NULL)
		return ;
	while (prompt[j++] && prompt[i] != NULL)
		if(prompt[i + 1] == NULL)
			ft_printf("%s", prompt[i++]);
		else
			ft_printf("%s ", prompt[i++]);
	if(new_line == true)
		printf("\n");
}

void ft_echo(char **prompt)
{
	int		i;
	int		j;
	bool	new_line;
	
	i = 1;
	j = 1;
	new_line = true;
	if (ft_strcmp(prompt[i++], "echo") == 0)
	{
		if(prompt[i] == NULL)
			return ;
		if (*prompt[i] != '\0' && ft_strncmp(prompt[i], "-n", 2) == 0)
		{
			while (ft_strncmp(prompt[i], "-n", 2) == 0)
			{
				if(handle_flag(prompt, i, j) == 0)
					break;
				new_line = false;
				i++;
				if(prompt[i] == NULL)
					return ;
			}
		}
		print_args(prompt, j, i, new_line);
	}
}

// int main(int ac, char **av)
// {
// 	(void)ac;
// 	ft_echo(av, av[3]);
// 	return (0);
// }