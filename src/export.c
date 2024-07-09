/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:19 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/09 16:33:28 by wnocchi          ###   ########.fr       */
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

void	ft_addnode(t_env **lst, t_env *add)
{
	t_env *last_node;
	
	if (!lst || !add)
		return ;
	if (!*lst)
		*lst = add;
	else
	{
		last_node = ft_lastnode(()*lst);
		last_node->next = add;
		add->prev = last_node;
	}
}

t_env *create_env_node(char **envp, int i)
{
	t_env *env;
	char **tmp;
	
	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->var = ft_strdup(envp[i]);
	if(!env->var)
		return (NULL);
	return (env);
}

t_msh *parsing(char *line, char **envp)
{
	(void)envp;
	t_env *env;
	t_env *tmp;
	char **splited;
	int	i;

	env = NULL;
	i = 0;
	splited = ft_split(line, '|');
	while (envp[i])
	{
		tmp = create_env_node(envp, i);
		ft_addnode(&env, tmp);
		i++;
	}
	free_tab(splited);
	return (env);
}

char **cpy_env(t_env *env, char **envp)
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

int	env_in_list(char **env, t_msh *msh)
{
	t_msh *current;

	current = ft_lastnode(msh);
	while(current)
	{
		if (current->my_env)
			free_tab(current->my_env);
		current->my_env = cpy_env(env);
		current = current->prev;
	}
	return (0);
}

int	add_var_env(char *av ,t_msh *msh)
{
	char **new_env;
	int i;

	i = 0;
	new_env = ft_calloc(sizeof(char *), env_len(msh->my_env) + 2);
	printf("env_len = %d\n", env_len(msh->my_env) + 1);
	while(msh->my_env[i])
	{
		new_env[i] = ft_strdup(msh->my_env[i]);
		printf("%d %s\n", i , new_env[i]);
		// if(!new_env[i])
		// 	return (free_tab(new_env), 1);	
		i++;
	}
	// printf("%d\n", i);
	new_env[i] = ft_strdup(av);
	if(env_in_list(new_env, msh))
		return (1);
	for(int i = 0; msh->my_env[i]; i++)
		printf("%s\n", msh->my_env[i]);
	free_tab(new_env);
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
	if(/* msh->cmd[0] &&  */msh->cmd[1])
		add_var_env(msh->cmd[1], msh);
	return (0);
}