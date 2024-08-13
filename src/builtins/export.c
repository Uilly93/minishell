/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:31:19 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/13 13:42:01 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	set_excode(&env, 0);
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
				return (free((void *)key), free((void *)value), false);
			}
			else
				return (free((void *)key), free((void *)value), true);
		}
		current = current->next;
	}
	return (free((void *)key), free((void *)value), false);
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
		return (ft_printf(2, "msh: export: `%s': not a valid identifier\n",
				msh->cmd[i]), true);
	key = get_key_env(msh->cmd[i]);
	while (key[j])
	{
		if (key[j] && !ft_isalnum(key[j]))
			return (ft_printf(2, "msh: export: `%s': not a valid identifier\n",
					msh->cmd[i]), free(key), true);
		j++;
	}
	free(key);
	return (false);
}

int	ft_export(t_msh *msh, t_env **env)
{
	t_env	*new_var;
	int		i;

	i = 0;
	if (msh->cmd[0] && !msh->cmd[1])
		return (export_print(msh, *env), 0);
	while (msh->cmd[++i])
	{
		if (msh->cmd[i][0] != 0 && check_errors(msh, i))
		{
			set_excode(env, 1);
			continue ;
		}
		if (var_already_exist(msh->cmd[i], env))
			continue ;
		new_var = ft_calloc(sizeof(t_env), 1);
		if (!new_var)
			return (set_excode(env, 1), 1);
		new_var->full_var = ft_strdup(msh->cmd[i]);
		new_var->key = get_key_env(msh->cmd[i]);
		new_var->value = get_value_env(msh->cmd[i]);
		add_env_node(env, new_var);
		set_excode(env, 0);
	}
	return (update_env(env), 0);
}
