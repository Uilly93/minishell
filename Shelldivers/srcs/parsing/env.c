/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsiefert <nsiefert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 11:41:53 by nate              #+#    #+#             */
/*   Updated: 2024/05/02 03:01:12 by nsiefert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Cat the differents paths from the defines.h file
char	*ft_strjoin_path(void)
{
	char	*str;

	str = ft_strjoin("PATH=", PATH1);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH2);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH3);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH4);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH5);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH6);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH7);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH8);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH9);
	str = ft_strjoin(str, ":");
	str = ft_strjoin(str, PATH10);
	return (str);
}

// Cat the actual shlvl in the ms_env cpy and increment de shl number
char	*ft_shlvl(char *str)
{
	int		shlvl;
	char	*str;

	shlvl = ft_atoi(str);
	shlvl++;
	str = ft_strjoin("SHLVL=", ft_itoa(shlvl));
	return(str);
}

t_data	*do_minim_env(t_data *data, char *str)
{
	data->ms_env = malloc(sizeof(char *) * 4);
	if (!data->ms_env)
		ft_error_free("Malloc problem !", data, 2);
	data->ms_env[0] = ft_strjoin("PWD=", getcwd(str, 0));
	data->ms_env[1] = ft_strjoin("SHLVL=", "1");
	data->ms_env[2] = ft_strjoin_path();
	data->ms_env[3] = NULL;
	return (data);
}

// Get the useful informations in my envp tab
t_data	*do_env(char **envp, t_data *data, char *str)
{
	int	i;

	i = -1;
	if (envp[0])
	{
		data->ms_env = malloc(sizeof(char *) * (ft_tabsize(data) + 1));
		if (!data->ms_env)
			ft_error_free("Malloc problem !",data, 2);
		while (envp[++i])
		{
			if (!ft_strncmp(envp[i],"SHLVL=", 6))
				data->ms_env[i] = ft_shlvl(envp[i]);
			else
				data->ms_env[i] = ft_strdup(envp[i]);
		}
		data->ms_env[i] = NULL;
		return (data);
	}
	data = do_minim_env(data, str);
	return (data);
}
