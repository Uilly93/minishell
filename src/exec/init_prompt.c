/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:40:15 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/10 13:05:11 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pwd_prompt(void)
{
	char	*line;
	char	*new_line;
	char	**pwd;
	int		i;

	i = 0;
	line = getcwd(NULL, 0);
	if (!line)
		return (NULL);
	pwd = ft_split(line, '/');
	free(line);
	if (!pwd)
		return (NULL);
	if (*pwd)
		while (pwd[i] != NULL)
			i++;
	if (i == 0)
		new_line = ft_strjoin("/", BOLD_BLUE"> "RESET);
	else
		new_line = ft_strjoin(pwd[i - 1], BOLD_BLUE"> "RESET);
	free_tab(pwd);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	*color_exit_prompt(t_env **env)
{
	const char	*exit_code = ft_itoa((*env)->ex_code);
	char		*res;

	if (!exit_code)
		return (NULL);
	if ((*env)->ex_code != 0)
		res = ft_strjoin(BOLD_RED, exit_code);
	else
		res = ft_strjoin(BOLD_GREEN, exit_code);
	free((void *)exit_code);
	exit_code = ft_strjoin(res, RESET" "BOLD_BLUE);
	free(res);
	return ((void *)exit_code);
}

char	*custom_prompt(t_env **env)
{
	char		*tmp;
	char		*custom_prompt;
	const char	*color_exit = color_exit_prompt(env);
	char		*emergency_prompt;

	if (!color_exit)
		return (NULL);
	tmp = pwd_prompt();
	if (!tmp)
	{
		emergency_prompt = ft_strjoin(color_exit,
				BOLD_RED"Emergency Prompt> "RESET);
		free((void *)color_exit);
		return (emergency_prompt);
	}
	custom_prompt = ft_strjoin(color_exit, tmp);
	free((void *)color_exit);
	free(tmp);
	if (!custom_prompt && !*custom_prompt)
		return (NULL);
	return (custom_prompt);
}
