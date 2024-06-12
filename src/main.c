/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:04:34 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/12 11:03:05 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/chardefs.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>

char **pipe_split(char *prompt)
{
	char **splited;
	
	splited = ft_split(prompt, '|');
	if (splited == NULL)
		return (NULL);
	return (splited);
}

void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

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
void	free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (tab[i])
			ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

char *pwd_prompt()
{
	char *line;
	char *new_line;
	char **pwd;
	int i;
	
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
	printf(BOLD_BLUE);
	if (i == 0)
		new_line = ft_strjoin("/", "> "RESET);
	else
		new_line = ft_strjoin(pwd[i - 1], "> "RESET);
	free_tab(pwd);
	return (new_line);
}


int	get_prompt(t_msh *msh, char *line, char *prompt)
{
	line = NULL;
	prompt = NULL;
	printf(BOLD_GREEN"➜  ");
	prompt = pwd_prompt();
	if (!prompt)
		return (printf(RESET), free(msh), 1);
	line = readline(prompt);
	if (line == NULL)
	{
		ft_free(msh);
		ft_free(prompt);
		return (1);
	}
	return (0);
}

char	**get_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (ft_split(envp[i], ':'));
		else
			i++;
	}
	return (NULL);
}

char	*join_path_access(char *av, char **envp)
{
	int		i;
	char	**s;
	char	*res;

	i = 0;
	res = NULL;
	s = get_path(envp);
	if (!s)
		return (write(2, "Error: no environment\n", 22), NULL);
	while (s[i])
	{
		res = ft_strcat_malloc(s[i], "/");
		if (!res)
			return (NULL);
		res = join_free(res, av);
		if (!res)
			return (NULL);
		if (access(res, X_OK) == 0)
			return (free_tab(s), res);
		free(res);
		i++;
	}
	free_tab(s);
	return (NULL);
}

int	close_pipes(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (0);
}

int is_it_builtin(char **cmd, t_msh *msh, char **envp)
{
	(void)envp;
	if (*cmd && ft_strcmp(*cmd, "<<") == 0)
		return (here_doc(msh, cmd), 1);
	if (*cmd && ft_strcmp(*cmd, "echo") == 0)
		return (ft_echo(cmd), 1);
	if (*cmd && ft_strcmp(*cmd, "cd") == 0)
		if (ft_cd(cmd) == 0)
			return (1);
	if (*cmd && ft_strcmp(*cmd, "pwd") == 0)
		return (get_pwd(cmd), 1);
	return (0);
}
int	test_child(char **envp, char **av)
{
	pid_t	child;
	char	*path;
	int status;
	// int		pipefd[2];

	child = fork();
	if (child == 0)
	{
		path = join_path_access(*av, envp);
		if(!path)
			return (free_tab(av), exit(127), 1);
		// redirect_fd_read(msh, pipefd);
		// redirect_fd_write(msh, pipefd);
		if(execve(path, av, envp) == -1)
			return (free_tab(av), free(path), exit(127), 1);
		free(path);
	}
	while (wait(&status) < 0)
		;
	status = WEXITSTATUS(status);
	return (0);
}

int	msh_loop(t_msh *msh, char **envp)
{	
	char *line = NULL;
	char *prompt = NULL;
	char **splited = NULL;
	
	while (1)
	{
		printf(BOLD_GREEN"➜  ");
		prompt = pwd_prompt();
		if (!prompt)
			return (printf(RESET), 1);
		line = readline(prompt);
		if (!line)
			return (ft_free(prompt), 1);
		splited = ft_split(line, ' ');
		if (!splited)
			return (ft_free(line), ft_free(prompt), 1);
		if(*splited && is_it_builtin(splited, msh, envp) == 0)
			test_child(envp, splited);
		if (*splited && ft_strcmp(*splited, "exit") == 0)
			break;
		free_tab(splited);
		ft_free(line);
		ft_free(prompt);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_msh msh = {0};// = ft_calloc(1, sizeof(t_msh));
	msh.out = 0;
	(void)ac;
	(void)av;
	msh_loop(&msh, envp);
	// ft_free(msh);
	return (0);
}
