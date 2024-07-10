/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:19 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/10 16:32:15 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

void test(t_env *env)
{
	t_env *current = env;
	int i = 0;

	while(current)
	{
		printf("%d = %s\n", i++, current->full_var);
		current = current->next;
	}
}

t_env	*ft_envlastnode(t_env *lst);

int	free_env(t_env *env)
{
	t_env *current;
	t_env *prev;

	current = env;
	while(current)
	{
		prev = current;
		free(current->full_var);
		current = current->next;
		free(prev);
	}
	return (0);
}

int	env_len(t_env *env)
{
	int		i;
	t_env	*current;

	current = env;
	i = 0;
	while(current)
	{
		current = current->next;
		i++;
	}
	return(i);
}

t_env	*ft_envlastnode(t_env *lst)
{
	t_env	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
		current = current->next;
	return (current);
}

void	add_env_node(t_env **lst, t_env *add)
{
	if (!lst || !add)
		return ;
	if (!*lst)
		*lst = add;
	else
		ft_envlastnode(*lst)->next = add;
}

t_env *create_env_node(char **envp, int i)
{
	t_env *env;
	
	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->full_var = ft_strdup(envp[i]);
	if(!env->full_var)
		return (NULL);
	return (env);
}

t_env *env_into_list(char **envp)
{
	t_env *env;
	t_env *tmp;
	int	i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = create_env_node(envp, i);
		// tmp->full_var = ft_strdup(envp[i]);
		add_env_node(&env, tmp);
		i++;
	}
	// test(env);
	return (env);
}

// t_env *cpy_env(t_env *env)
// {
// 	t_env *cpy;
// 	t_env *tmp;
// 	t_env *current;

// 	cpy = NULL;
// 	while(current)
// 	{
// 		tmp = create_env_node();
// 		tmp->full_var = ft_strdup(current->full_var);
// 		add_env_node(&cpy, tmp);	
// 		current = current->next;
		
// 	}
// }

char **get_env(t_env *env)
{
	int i;
	char **cpy;
	t_env *current;

	current = env;
	i = 0;
	cpy = ft_calloc(sizeof(char *), env_len(env) + 1);
	// printf("%d\n", env_len(env));
	while(current)
	{
		cpy[i] = ft_strdup(current->full_var);
		// printf("%s\n", cpy[i]);
		current = current->next;
		i++;
	}
	return (cpy);
}

// int	env_in_list(char **env, t_msh *msh)
// {
// 	t_msh *current;

// 	current = ft_lastnode(msh);
// 	while(current)
// 	{
// 		if (current->my_env)
// 			free_tab(current->my_env);
// 		current->my_env = cpy_env(env);
// 		current = current->prev;
// 	}
// 	return (0);
// }

// int	add_var_env(char *av ,t_env *env)
// {
// 	char **new_env;
// 	int i;

// 	i = 0;
// 	new_env = ft_calloc(sizeof(char *), env_len(msh->my_env) + 2);
// 	printf("env_len = %d\n", env_len(msh->my_env) + 1);
// 	while(msh->my_env[i])
// 	{
// 		new_env[i] = ft_strdup(msh->my_env[i]);
// 		printf("%d %s\n", i , new_env[i]);
// 		// if(!new_env[i])
// 		// 	return (free_tab(new_env), 1);	
// 		i++;
// 	}
// 	// printf("%d\n", i);
// 	new_env[i] = ft_strdup(av);
// 	if(env_in_list(new_env, msh))
// 		return (1);
// 	for(int i = 0; msh->my_env[i]; i++)
// 		printf("%s\n", msh->my_env[i]);
// 	free_tab(new_env);
// 	return (0);
// }

void	ft_swap_tab(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_print_env(char **tab, t_msh *msh, t_env *env)
{
	int	i;

	i = 0;
	while (i < env_len(env) - 1)
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

int	env_print(t_msh *msh, t_env *env)
{
	char	**cpy;
	
	cpy = get_env(env);
	if(!cpy)
		return (1);
	sort_print_env(cpy, msh ,env);
	free_tab(cpy);
	return (0);
}

int	ft_export(t_msh *msh, t_env *env)
{
	t_env	*new_var;
	
	if(msh->cmd[0] && !msh->cmd[1])
	{
		// test(msh->env);
		// printf("test\n");
		env_print(msh, env);
		return (0);
	}
	if(msh->cmd[0] && msh->cmd[1])
	{
		new_var = ft_calloc(sizeof(t_env), 1);
		if(!new_var)
			return (1);
		new_var->full_var = ft_strdup(msh->cmd[1]);
		add_env_node(&env, new_var);
	}
	return (0);
}