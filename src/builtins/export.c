/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:19 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/24 15:52:21 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//------------------env_manage.c--------------------

int	free_env(t_env *env)
{
	t_env	*current;
	t_env	*prev;

	current = env;
	while (current)
	{
		prev = current;
		free(current->value);
		free(current->full_var);
		free(current->key);
		free_tab(current->full_env);
		current = current->next;
		free(prev);
	}
	env = NULL;
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
	return (i);
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

t_env	*create_env_node(char **envp, int i)
{
	t_env	*env;

	env = ft_calloc(sizeof(t_env), 1);
	if (!env)
		return (NULL);
	env->full_var = ft_strdup(envp[i]);
	if (!env->full_var)
		return (NULL);
	return (env);
}

//------------------env_create.c------------------

t_env	*env_into_list(char **envp)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	if (!*envp)
		return (NULL);
	env = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = create_env_node(envp, i);
		add_env_node(&env, tmp);
		i++;
	}
	update_env(env);
	split_env(env);
	return (env);
}

char *join_name_var(t_env *env)
{
	char	*tmp;
	char	*res;

	if (!env->value)
		return (ft_strjoin(env->key, "="));
	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, env->value);
	free(tmp);
	if (!res)
		return (NULL);
	return (res);
}

char **get_env(t_env *env)
{
	int			i;
	const char	**cpy = ft_calloc(sizeof(char *), env_len(env) + 1);
	t_env		*current;

	if (!cpy)
		return (NULL);
	current = env;
	i = 0;
	while (current)
	{
		if (is_equal(current->full_var))
			cpy[i] = join_name_var(current);
		else
			cpy[i] = ft_strdup(current->key);
		if (!cpy[i])
			return (free_tab((char **)cpy), NULL);
		current = current->next;
		i++;
	}
	return ((char **)cpy);
}

// -----------------------export_print.c---------------------------

void	ft_swap_tab(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	**sort_env(char **tab, t_env *env)
{
	int			i;
	const char	**sorted = ft_calloc(sizeof(char *), env_len(env) + 1);

	if (!sorted)
		return (NULL);
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
	while (tab[i] != NULL)
	{
		sorted[i] = ft_strdup(tab[i]);
		if (!sorted[i])
			return (free_tab((char **)sorted), NULL);
		i++;
	}
	return ((char **)sorted);
}

int	print_line(char *line, int fd)
{
	const char	*value = get_value_env(line);
	const char	*name = get_key_env(line);

	if (fd == -1)
		return (free((void *)name), free((void *)value), perror("msh"), 1);
	if (!name)
		return (free((void *)value), 1);
	if (value)
		ft_printf(fd, "declare -x %s=\"%s\"\n", name, value);
	else
		ft_printf(fd, "declare -x %s\n", name);
	free((void *)name);
	free((void *)value);
	return (0);
}

int	print_export(char **sorted, t_msh *msh)
{
	int			i;
	const int	fd = which_fd(msh);

	if (fd == -1)
		return (perror("msh"), 1);
	i = 0;
	while (sorted[i])
	{
		if (print_line(sorted[i], fd))
			return (1);
		i++;
	}
	return (0);
}

//---------------------export_utils.c-----------------------------------

char *join_vars(char *av, char *value)
{
	char	*add;
	char	*tmp;

	add = get_value_env(av);
	if (!value)
		return (add);
	tmp = ft_strdup(value);
	if (!tmp)
		return (free(add), NULL);
	free(value);
	value = ft_strjoin(tmp, add);
	free(add);
	free(tmp);
	if (!value)
		return (NULL);
	return (value);
}


bool	update_it(char *av, t_env *current, const char *v, const char *v_name)
{
		free(current->full_var);
		current->full_var = ft_strdup(av);
		current->value = join_vars(av, current->value);
		free((void*)v_name);
		free((void*)v);
		return (true);
}

// -----------------export.c-----------------

int	export_print(t_msh *msh, t_env *env)
{
	char	**cpy;
	char	**sorted;

	cpy = get_env(env);
	if (!cpy)
		return (1);
	sorted = sort_env(cpy, env);
	if (!sorted)
		return (free_tab(cpy), 1);
	print_export(sorted, msh);
	free_tab(sorted);
	free_tab(cpy);
	return (0);
}

bool	update_var(char *av, t_env **env, const char *value, const char *key)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (key && ft_strcmp((char *)key, current->key) == 0)
		{
			if (is_equal(av) == 2)
				return (update_it(av, current, value, key));
			else if (is_equal(av) == 1)
			{
			 	ft_del_node(env, (char *)key);
				return (free((void*)key), free((void*)value), false);
			}
			else
				return (free((void*)key), free((void*)value), true);
		}
		current = current->next;
	}
	return (free((void*)key), free((void*)value), false);
}

bool	var_already_exist(char *av, t_env **env)
{
	char	*key;
	char	*value;

	key = get_key_env(av);
	value = get_value_env(av);
	return (update_var(av, env, value, key));
}

bool	check_errors(t_msh *msh, int i)
{
	int		j;
	char	*key;

	j = 1;
	if (msh->cmd[i][0] && !ft_isalpha(msh->cmd[i][0]))
			return (ft_printf(2, "1 msh: export: `%s': not a valid identifier\n",
					msh->cmd[i]), true);
	key = get_key_env(msh->cmd[i]);
	while (key[j])
	{
		if (key[j] && !ft_isalnum(key[j]))
			return (ft_printf(2, "3 msh: export: `%s': not a valid identifier\n",
				msh->cmd[i]), free(key), true);
		j++;
	}
	free(key);
	return (false);
}

int	ft_export(t_msh *msh, t_env *env)
{
	t_env	*new_var;
	int		i;

	i = 0;
	if (msh->cmd[0] && !msh->cmd[1])
		return (export_print(msh, env), 0);
	while (msh->cmd[++i])
	{
		if (check_errors(msh, i))
			continue ;
		if (var_already_exist(msh->cmd[i], &env))
			continue ;
		new_var = ft_calloc(sizeof(t_env), 1);
		if (!new_var)
			return (1);
		new_var->full_var = ft_strdup(msh->cmd[i]);
		new_var->key = get_key_env(msh->cmd[i]);
		new_var->value = get_value_env(msh->cmd[i]);
		add_env_node(&env, new_var);
	}
	update_env(env);
	return (0);
}
