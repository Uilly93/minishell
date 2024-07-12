/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:19 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/12 11:48:40 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int test(t_env *env)
{
	t_env *current = env;
	int i = 0;

	split_env(env);
	while (current)
	{
		// if (current->full_var != NULL)
		// 	printf("%d = %s\n", i, current->full_var);
		printf("%s=%s\n", current->var_name, current->var);
		current = current->next;
		i++;
	}
	return (0);
}

t_env	*ft_envlastnode(t_env *lst);

int	free_env(t_env *env)
{
	t_env *current;
	t_env *prev;

	current = env;
	while (current)
	{
		prev = current;
		free(current->full_var);
		free(current->var);
		free(current->var_name);
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
	while (current)
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
	env->set = 1;
	// printf("%d\n", env->set);
	env->full_var = ft_strdup(envp[i]);
	if (!env->full_var)
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
		add_env_node(&env, tmp);
		i++;
	}
	split_env(env);
	return (env);
}

char **get_env(t_env *env)
{
	int i;
	char **cpy;
	char *tmp;
	t_env *current;

	current = env;
	i = 0;
	cpy = ft_calloc(sizeof(char *), env_len(env) + 1);
	while (current)
	{
		tmp = ft_strjoin(current->var_name, "=");
		if (!tmp)
			return(free_tab(cpy), NULL);
		if(current->set == 1)
			cpy[i] = ft_strjoin(tmp, current->var);
		else
			cpy[i] = ft_strdup("");
		free(tmp);
		if (!cpy[i])
			return(free_tab(cpy), NULL);
		current = current->next;
		i++;
	}
	return (cpy);
}

void	ft_swap_tab(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	**sort_env(char **tab, t_env *env)
{
	int	i;
	char **sorted;

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
	sorted = ft_calloc(sizeof(char *), env_len(env) + 1);
	if (!sorted)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		sorted[i] = ft_strdup(tab[i]);
		i++;
	}
	return(sorted);
}

int	print_export(char **sorted, t_msh *msh)
{
	char	*var;
	char	*name;
	int		i;

	i = 0;
	while (sorted[i])
	{
		name = get_var_name(sorted[i]);
		if (!name)
			return(1);
		var = get_var(sorted[i]);
		if (!var)
			return(1);
		if(*name && *var)
			ft_printf(which_fd(msh), "define -x %s=\"%s\"\n", name, var);
		free(name);
		free(var);
		i++;
	}
	free_tab(sorted);
	return (0);
}

int	env_print(t_msh *msh, t_env *env)
{
	char	**cpy;
	char	**sorted;
	
	cpy = get_env(env);
	if (!cpy)
		return (1);
	sorted = sort_env(cpy, env);
	if (!sorted)
		return(free_tab(cpy), 1);
	print_export(sorted, msh);
	free_tab(cpy);
	return (0);
}

char *join_vars(char *av, char *var)
{
	char	*add;
	char	*tmp;

	add = get_var(av);
	if (!add)
		return (NULL);
	tmp = ft_strdup(var);
	if (!tmp)
		return (free(add), NULL);
	free(var);
	var = ft_strjoin(tmp, add);
	free(add);
	free(tmp);
	if (!var)
		return (NULL);
	return (var);
}

bool	var_already_exist(char *av, t_env *env)
{
	t_env		*current;
	const char	*var_name = get_var_name(av);

	current = env;
	while (current)
	{
		if (var_name && ft_strcmp((char *)var_name, current->var_name) == 0)
		{
			if(current->set == 0)
				return (free((void*)var_name), false);
			if (is_equal(av) == 2)
			{
				current->var = join_vars(av, current->var);
				return (free((void*)var_name), true);
			}
			else
			{
				free(current->var);
				return (current->var = get_var(av), free((void*)var_name), true);
			}
		}
		current = current->next;
	}
	return (free((void*)var_name), false);
}

int	ft_export(t_msh *msh, t_env *env)
{
	t_env	*new_var;
	int		i;

	i = 1;
	if (msh->cmd[0] && !msh->cmd[1])
		return(env_print(msh, env), 0);
	while (msh->cmd[i])
	{
		if (var_already_exist(msh->cmd[i], env))
		{
			i++;
			continue ;
		}
		new_var = ft_calloc(sizeof(t_env), 1);
		if (!new_var)
			return (1);
		if (msh->cmd[i] && is_equal(msh->cmd[i]))
			new_var->set = true;
		new_var->full_var = ft_strdup(msh->cmd[i]);
		new_var->var_name = get_var_name(msh->cmd[i]);
		new_var->var = get_var(msh->cmd[i]);
		add_env_node(&env, new_var);
		i++;
	}
	return (0);
}
