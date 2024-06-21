/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:04:34 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/21 10:34:50 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <errno.h>
#include <readline/chardefs.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <readline/history.h>

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

t_msh	*ft_lastnode(t_msh *lst);

int	close_fds(int *pipefd, t_msh *msh)
{
	(void)pipefd;
	t_msh	*current;

	current = msh;//ft_lastnode(msh);
	while(current)
	{
		if(current->pipefd[0] != -1)
			close(pipefd[0]);
		if(current->pipefd[1] != -1)
			close(pipefd[1]);
		current = current->prev;
	}
	return (0);
}

int is_it_builtin(char **cmd, t_msh *msh, char **envp)
{
	(void)envp;
	if (*cmd && ft_strcmp(*cmd, "<<") == 0)
		return (here_doc(msh, cmd), 1);
	// if (*cmd && ft_strcmp(*cmd, "echo") == 0)
	// 	return (ft_echo(cmd), 1);
	if (*cmd && ft_strcmp(*cmd, "cd") == 0)
		if (ft_cd(cmd) == 0)
			return (1);
	if (*cmd && ft_strcmp(*cmd, "pwd") == 0)
		return (get_pwd(cmd), 1);
	return (0);
}

void	free_lst(t_msh *msh);

int	test_child(t_msh *msh, char **envp)
{
	static int i = 0;
	pid_t	child;
	char	*path;
	// int		status;

	child = fork();
	if (child == 0)
	{
		path = join_path_access(*msh->cmd, envp);
		if(!path)
			return (free_lst(msh), exit(127), 1);
		redirect_fd(msh/* , pipefd */);
		i++;
		close_fds(msh->pipefd, msh);
		if(execve(path, msh->cmd, envp) == -1)
		{
			perror("msh :");
			return (free_lst(msh), free(msh), free(path), exit(127), 1);
		}
		free(path);
	}
	return (0);
}


t_msh	*ft_lastnode(t_msh *lst)
{
	t_msh	*current;

	if (!lst)
		return (0);
	current = lst;
	while (current->next)
	{
		current = current->next;
	}
	return (current);
}

void	ft_addnode(t_msh **lst, t_msh *add)
{
	t_msh *last_node;
	
	if (!lst || !add)
		return ;
	if (!*lst)
		*lst = add;
	else
	{
		last_node = ft_lastnode(*lst);
		last_node->next = add;
		add->prev = last_node;
	}
}

int	ft_lstlen(t_msh *msh)
{
	t_msh	*current;
	int		i;

	if (!msh)
		return (0);
	current = msh;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

void	print_node(t_msh *msh)
{
	t_msh *current;

	current = msh;
	int i = 1;
	int j = 0;
	printf("-----------------------------------------\n");
	printf("lst size = %d\n", ft_lstlen(msh));
	while(current)
	{
		printf("cmd %d = ", current->index);
		j = 0;
		while(current->cmd[j])
		{
			printf("%s ", current->cmd[j]);
			j++;
		}
		printf("\n");
		current = current->next;
		if (current == NULL)
			break ;
		i++;
	}
	printf("-----------------------------------------\n");
}
 
t_msh *cmd_node(char *line)
{
	t_msh *msh;
	// char **tmp;
	
	// msh = NULL;
	msh = malloc(sizeof(t_msh));
	if(!msh)
		return (NULL);
	msh->in = -1;
	msh->out = -1;
	msh->cmd = ft_split(line, ' ');
	if (!msh->cmd)
		return (NULL);
	msh->next = NULL;
	msh->prev = NULL;
	return(msh);
}

t_msh *parsing(char *line)
{
	t_msh *msh;
	t_msh *tmp;
	char **splited;
	int	i;

	msh = NULL;
	// char *s = malloc(sizeof(char) * )
	i = 0;
	splited = ft_split(line, '|');
	while(splited[i])
	{
		tmp = cmd_node(splited[i]);
		tmp->pipefd[1] = -1;
		tmp->pipefd[0] = -1;
		tmp->index = i + 1;
		ft_addnode(&msh, tmp);
		i++;
	}
	free_tab(splited);
	return (msh);
}

void	free_lst(t_msh *msh)
{
	t_msh	*current;
	t_msh	*prev;

	current = msh;
	while (current)
	{
		free_tab(current->cmd);
		// close_fds(current->pipefd, msh);
		close(current->pipefd[0]);
		close(current->pipefd[1]);
		prev = current;
		current = current->next;
		free(prev);
	}
}

int exec(t_msh *msh, char **envp)
{
	t_msh *current;
	t_msh *prev;
	// int pipefd[2];

	current = msh;
	print_node(msh);
	while(current)
	{
		prev = current;
		// if (join_path_access(msh->cmd[0], envp) == NULL)
		// {
		// 	close_fds(pipefd, msh);
		// 	printf("%s: command not found\n", msh->cmd[0]);
		// }
		// close(current->pipefd[1]);
		pipe(current->pipefd);
		if(is_it_builtin(current->cmd, current, envp) == 0)
			test_child(current, envp);
		// if(!current->next)
		if(current->next == NULL)
			close_fds(msh->pipefd, msh);
		current = current->next;
		// pipe(current->pipefd);
	}
	close_fds(msh->pipefd, msh);
	// close(current->pipefd[1]);
	// close(current->pipefd[0]);
	free_lst(msh);
	while (wait(NULL) > 0)
		;
	
	return (0);
}

int	msh_loop(t_msh *msh, char **envp)
{	
	(void)envp;
	char *line;
	char *prompt;
	
	while (1)
	{
		printf(BOLD_GREEN"➜  ");
		prompt = pwd_prompt();
		if (!prompt)
			return (printf(RESET), 1);
		line = readline(prompt);
		free(prompt);
		if (!line)
			return (1);
		add_history(line);
		msh = parsing(line);
		exec(msh, envp);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_msh msh = {0};
	(void)ac;
	(void)av;
	msh_loop(&msh, envp);
	return (0);
}
