/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:04:34 by wnocchi           #+#    #+#             */
/*   Updated: 2024/05/30 14:27:00 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/chardefs.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

char *skip_chars(char *line)
{
	char *new_line;
	int i;
	int count;
	
	count = 0;
	i = 0;
	while (count < 3 && line[i])
	{
		if (line[i++] == '/')
			count++;
		else
			i++;
	}
	new_line = ft_strdup(line + i);
	free(line);
	return (new_line);
}

char *pwd_prompt()
{
	char *line;
	int count;
	
	count = 0;
	line = getcwd(NULL, 0);
	if (!line)
		return (NULL);
	line = skip_chars(line);
	printf(BOLD_BLUE);
	// printf(BG_BLUE);
	line = join_free(line, "> "RESET);
	return (line);
}
void	ft_free(void *ptr)
{
	if(ptr)
		free(ptr);
	// return (NULL);
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		if(tab[i])
			ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

int main(int ac, char **av)
{
	t_msh *msh = malloc(sizeof(t_msh));
	char *line;
	char *prompt;
	char **splited = NULL;
	(void)ac;
	(void)av;

	while(1)
	{
		printf(BOLD_GREEN"➜  ");
		prompt = pwd_prompt();
		if(!prompt)
			return (printf(RESET), free(msh), 1);
		line = readline(prompt);
		if(line == NULL)
		{
			ft_free(msh);
			ft_free(prompt);
			return(1);
		}
		splited = ft_split(line, ' ');
		if(!splited)
		{
			ft_free(line);
			ft_free(prompt);
			ft_free(msh);
			return (1);
		}
		if (*splited && ft_strcmp(*splited, "exit") == 0)
			break;
		free_tab(splited);
		ft_free(line);
		ft_free(prompt);	
	}
	free_tab(splited);
	ft_free(line);
	ft_free(prompt);
	ft_free(msh);
	return (0);
}
