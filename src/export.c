/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:19 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/05 16:58:23 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>


int	env_len(char **envp)
{
	int i;

	i = 0;
	while(envp[i])
		i++;
	return (i);
}

char **cpy_env(char **envp)
{
	int i;
	char **cpy;

	i = 0;
	if(envp == NULL)
		return (NULL);
	cpy = ft_calloc(sizeof(char *), env_len(envp) + 1);
	while(envp[i])
	{
		cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	return (cpy);
}

int	add_var_env(char *av ,t_msh *msh)
{
	char **new_env;
	int i;

	i = 0;
	new_env = ft_calloc(sizeof(char *), env_len(msh->my_env) + 2);
	while(msh->my_env[i])
	{
		new_env[i] = ft_strdup(msh->my_env[i]);
		if(!new_env[i])
			return (free_tab(new_env), 1);	
		i++;
	}
	new_env[i] = ft_strdup(av);
	free_tab(msh->my_env);
	msh->my_env = cpy_env(new_env);
	if(!msh->my_env)
		return (1);
	return (0);
}

void	ft_swap_tab(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_print_tab(char **tab, t_msh *msh)
{
	int	i;

	i = 0;
	while (i < (env_len(tab) - 1))
	{
		if (ft_strcmp(tab[i], tab[i + 1]) > 0)
		{
			ft_swap_tab(&tab[i], &tab[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	i = 0;
	while(tab[i] != NULL)
		ft_printf(which_fd(msh), "declare -x %s\n", tab[i++]);
}

int	env_print(t_msh *msh)
{
	char	**cpy;
	
	cpy = cpy_env(msh->my_env);
	if(!cpy)
		return (1);
	sort_print_tab(cpy, msh);
	free_tab(cpy);
	return (0);
}

int	ft_export(t_msh *msh)
{
	if(msh->cmd[0] && !msh->cmd[1])
		env_print(msh);
	if(msh->cmd[0] && msh->cmd[1])
		add_var_env(msh->cmd[1], msh);
	return (0);
}