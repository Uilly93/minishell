/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:04:34 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/03 10:26:47 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <bits/types/siginfo_t.h>
#include <readline/chardefs.h>
#include <readline/readline.h>
#include <readline/rltypedefs.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <readline/history.h>


void	ft_free(void *ptr)
{
	if (ptr)
		free(ptr);
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
	if (i == 0)
		new_line = ft_strjoin("/", BOLD_BLUE"> "RESET);
	else
		new_line = ft_strjoin(pwd[i - 1], BOLD_BLUE"> "RESET);
	free_tab(pwd);
	if(!new_line)
		return (NULL);
	return (new_line);
}

char *custom_prompt()
{
	char *tmp;
	char *custom_prompt;
	
	tmp = pwd_prompt();
	if(!tmp)
		return (NULL);
	custom_prompt = ft_strjoin(BOLD_GREEN"➜  "BOLD_BLUE, tmp);
	free(tmp);
	if(!custom_prompt)
		return (NULL);
	return(custom_prompt);
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
	if (access(av, X_OK) == 0)
		return (av);
	s = get_path(envp);
	while (s[i++])
	{
		res = ft_strjoin(s[i], "/");
		if (!res)
			return (free_tab(s), NULL);
		res = join_free(res, av);
		if (!res)
			return (free_tab(s), NULL);
		if (access(res, X_OK) == 0)
			return (free_tab(s), res);
		free(res);
	}
	free_tab(s);
	return (NULL);
}

t_msh	*ft_lastnode(t_msh *lst);

int	close_pipes(t_msh *msh)
{
	t_msh	*current;

	current = ft_lastnode(msh);
	while (current)
	{
		if (current->pipefd[0] != -1)
			close(current->pipefd[0]);
		if (current->pipefd[1] != -1)
			close(current->pipefd[1]);
		close_files(current);
		current = current->prev;
	}
	return (0);
}

int is_it_builtin(char **cmd, t_msh *msh, char **envp)
{
	(void)envp;
	if (cmd[0] && ft_strcmp(cmd[0], "<<") == 0)
		return (here_doc(msh, cmd), 1);
	if (cmd[0] && ft_strcmp(cmd[0], "echo") == 0)
		return (ft_echo(msh), 1);
	if (cmd[0] && ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd, envp), 1);
	if (cmd[0] && ft_strcmp(cmd[0], "pwd") == 0)
		return (get_pwd(cmd, msh), 1);
	return (0);
}

void	free_lst(t_msh *msh);

int	test_child(t_msh *msh, char **envp) // rename
{
	pid_t	child;
	char	*path;

	child = fork();
	if (child == 0)
	{
		path = join_path_access(msh->cmd[0], envp);
		if (!path)
		{
			ft_err("msh: command not found");
			return (free_lst(msh), exit(127), 1);
		}
		if (redirect_fd(msh))
			return (free_lst(msh), free(path), exit(127), 1);
		if (execve(path, msh->cmd, envp) == -1)
		{
			perror("msh");
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
		current = current->next;
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

void	print_node(t_msh *msh) // testing
{
	t_msh *current;

	current = msh;
	int i = 1;
	int j = 0;
	printf("-----------------------------------------\n");
	printf("lst size = %d\n", ft_lstlen(msh));
	while (current)
	{
		printf("cmd %d = ", current->index);
		j = 0;
		while (current->cmd[j])
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
	
	msh = ft_calloc(sizeof(t_msh), 1);
	if (!msh)
		return (NULL);
	msh->in = -1;
	msh->out = -1;
	msh->out_appen = 0;
	// msh->infile = "/tmp/heredoc_1";
	// msh->outfile = "outfile";
	msh->cmd = ft_split(line, ' ');
	if (!msh->cmd)
		return (NULL);
	return (msh);
}

t_msh *parsing(char *line)
{
	t_msh *msh;
	t_msh *tmp;
	char **splited;
	int	i;

	msh = NULL;
	i = 0;
	splited = ft_split(line, '|');
	while (splited[i])
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
	t_msh	*next;

	current = ft_lastnode(msh);
	while (current)
	{
		free_tab(current->cmd);
		if(current->hlimit)
			free(current->hlimit);
		close_files(current);
		next = current;
		current = current->prev;
		free(next);
	}
}

int exec(t_msh *msh, char **envp)
{
	t_msh *current;
	t_msh *prev;

	current = msh;
	while (current)
	{
		prev = current;
		if (ft_lstlen(msh) > 1)
			pipe(current->pipefd);
		if (is_it_builtin(current->cmd, current, envp) == 0)
			test_child(current, envp);
		current = current->next;
	}
	free_lst(msh);
	while (wait(NULL) > 0)
		;
	
	return (0);
}

void signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if(sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = true;
	}
	else if(sig == SIGQUIT)
	{
		;
	}
}

void void_func(void)
{
	return ;
}

int	init_sigint()
{
	struct sigaction sa;
    sa.sa_sigaction = signal_handler;
    sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	rl_event_hook = (void *)void_func;
    sa.sa_flags = 0;

    if (sigaction(SIGINT, &sa, NULL) == -1)
	{
        perror("sigaction failed for SIGINT");
        return (1);
    }
	sa.sa_handler = SIG_IGN;
    if (sigaction(SIGQUIT, &sa, NULL) == -1) {
        perror("sigaction failed for SIGQUIT");
        return (1);
    }
	return (0);
}

int	msh_loop(t_msh *msh, char **envp)
{	
	char *line;
	char *prompt;

	init_sigint();
	while (1)
	{
		prompt = custom_prompt();
		if (!prompt)
			return (printf(RESET), 1);
		line = readline(prompt);
		free(prompt);
		if (!line)
			return (1);
		if (ft_strlen(line))
			add_history(line);
		msh = parsing(line);
		exec(msh, envp);
	}
	return (0);
}

int main(int ac, char **av, char **envp)
{
	t_msh msh;
	ft_bzero(&msh, sizeof(t_msh));
	(void)ac;
	(void)av;
	msh_loop(&msh, envp);
	return (0);
}
