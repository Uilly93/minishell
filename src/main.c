/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 10:04:34 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/08 13:50:42 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <unistd.h>

void	set_excode(t_env **env, int code)
{
	t_env *current;

	current = *env;
	while (current)
	{
		current->ex_code = code;
		current = current->next;
	}
}

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
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

char *color_exit_prompt(t_env **env)
{
	char *exit_code = ft_itoa((*env)->ex_code);
	char *res;
	
	if(!exit_code)
		return NULL;
	if((*env)->ex_code != 0)
		res = ft_strjoin(BOLD_RED, exit_code);
	else
		res = ft_strjoin(BOLD_GREEN, exit_code);
	free(exit_code);
	exit_code = ft_strjoin(res, RESET" "BOLD_BLUE);
	free(res);
	return (exit_code);
}

char *custom_prompt(t_env **env)
{
	// (void)env;
	char *tmp;
	char *custom_prompt;
	const char	*color_exit = color_exit_prompt(env);
	
	if(!color_exit)
		return (NULL);
	tmp = pwd_prompt();
	if(!tmp)
		return (NULL);
	custom_prompt = ft_strjoin(color_exit, tmp);
	free((void *)color_exit);
	free(tmp);
	if(!custom_prompt)
		return (NULL);
	return(custom_prompt);
}

char	**get_path(t_env *env)
{
	t_env	*current;

	current = env;
	if(!current)
		return (NULL);
	while(current)
	{
		if (ft_strcmp("PATH", current->key) == 0)
			return (ft_split(current->value, ':'));
		else
			current = current->next;
	}
	return (NULL);
}

char	*join_path_access(char *av, t_env *env)
{
	int		i;
	char	**s;
	char	*res;

	i = -1;
	if (access(av, X_OK) == 0)
		return (ft_strdup(av));
	s = get_path(env);
	if(!s)
		return (NULL);
	while (s[++i])
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

int is_it_builtin(char **cmd, t_msh *msh, t_env **env)
{
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "echo") == 0)
		return (set_excode(&msh->env, 0), ft_echo(msh), 1);
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "cd") == 0)
		return (ft_cd(cmd, env), 1);
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "pwd") == 0)
		return (get_pwd(cmd, msh), 1);
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "exit") == 0)
		return (set_excode(env, ft_exit(msh, env)), 1);
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "export") == 0)
		return (ft_export(msh, env), 1);
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "env") == 0)
		return (set_excode(env, ft_env(env, msh)), 1);
	if (cmd && cmd[0] && ft_strcmp(cmd[0], "unset") == 0)
		return (set_excode(env, ft_unset(env, cmd)), 1);
	return (0);
}

void	free_lst(t_msh *msh);



int	create_child(t_msh *msh, t_env **env)
{
	pid_t	child;
	char	*path;

	child = fork();
	if(child == -1)
		perror("msh");
	if (child == 0)
	{
		path = join_path_access(msh->cmd[0], msh->env);
		if (!path)
		{
			ft_printf(2, "msh: %s: command not found\n", msh->cmd[0]);
			set_excode(env, 127);
			return (free_env(env), free_lst(msh), exit(127), 127);
		}
		if (redirect_fd(msh))
			return (free_env(env), free_lst(msh), free(path), exit(127), 1);
		if (execve(path, msh->cmd, NULL) == -1)
		{
			perror("msh");
			return (free_env(env), free_lst(msh), free(path), exit(127), 1);
		}
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

// void	ft_addnode(t_msh **lst, t_msh *add)
// {
// 	t_msh *last_node;
	
// 	if (!lst || !add)
// 		return ;
// 	if (!*lst)
// 		*lst = add;
// 	else
// 	{
// 		last_node = ft_lastnode(*lst);
// 		last_node->next = add;
// 		add->prev = last_node;
// 	}
// }

int	ft_lstlen(t_msh *msh)
{
	t_msh	*current;
	int		i;

	if (!msh)
		return (0);
	current = ft_lastnode(msh);
	i = 0;
	while (current)
	{
		current = current->prev;
		i++;
	}
	return (i);
}

// void	print_node(t_msh *msh) // testing
// {
// 	t_msh *current;

// 	current = msh;
// 	int i = 1;
// 	int j = 0;
// 	printf("-----------------------------------------\n");
// 	printf("lst size = %d\n", ft_lstlen(msh));
// 	while (current)
// 	{
// 		printf("cmd %d = ", current->index);
// 		j = 0;
// 		while (current->cmd[j])
// 		{
// 			printf("%s ", current->cmd[j]);
// 			j++;
// 		}
// 		printf("\n");
// 		current = current->next;
// 		if (current == NULL)
// 			break ;
// 		i++;
// 	}
// 	printf("-----------------------------------------\n");
// }
 
// t_msh *cmd_node(char *line)
// {
// 	t_msh *msh;
	
// 	msh = ft_calloc(sizeof(t_msh), 1);
// 	if (!msh)
// 		return (NULL);
// 	msh->in = -1;
// 	msh->out = -1;
// 	msh->append = 0;
// 	// msh->infile = "/tmp/heredoc_1";
// 	// msh->outfile = "outfile";
// 	msh->cmd = ft_split(line, ' ');
// 	if (!msh->cmd)
// 		return (NULL);
// 	return (msh);
// }

// t_msh *my_parsing(char *line, t_env *env)
// {
// 	t_msh	*msh;
// 	t_msh	*tmp;
// 	char	**splited;
// 	int	i;

// 	msh = NULL;
// 	i = 0;
// 	splited = ft_split(line, '|');
// 	while (splited[i])
// 	{
// 		tmp = cmd_node(splited[i]);
// 		tmp->env = env;
// 		tmp->pipefd[1] = -1;
// 		tmp->pipefd[0] = -1;
// 		tmp->index = i + 1;
// 		ft_addnode(&msh, tmp);
// 		i++;
// 	}
// 	free_tab(splited);
// 	return (msh);
// }

void	free_lst(t_msh *msh)
{
	t_msh	*current;
	t_msh	*next;

	current = ft_lastnode(msh);
	while (current)
	{
		close_files(current);
		if(current->outfile)
			free(current->outfile);
		if(current->infile)
			free(current->infile);
		free_tab(current->cmd);
		next = current;
		current = current->prev;
		free(next);
	}
}
int	check_and_open(t_msh *msh)
{
	if(msh->here_doc == 1 && msh->infile != NULL)
		if(here_doc(msh)== SIGINT)
			return (SIGINT);
	if (msh->infile != NULL && msh->here_doc == 0)
	{
		msh->in = open(msh->infile, O_WRONLY, 0644);
		if (msh->in == -1)
			return (perror("msh"), close_pipes(msh), close_files(msh), 1);
	}
	if (msh->outfile != NULL)
	{
		msh->out = open(msh->outfile, get_flags(msh), 0644);
		if (msh->out == -1)
			return (perror("msh"), close_pipes(msh), close_files(msh), 1);
	}
	close_files(msh);
	return (0);
}

int exec(t_msh *msh, t_env **env)
{
	t_msh *current;

	current = msh;
	while (current)
	{
		if(check_and_open(current) != 0)
		{
			set_excode(env, 1);
			current = current->next;
			continue ;
		}
		if (ft_lstlen(msh) > 1)
			pipe(current->pipefd);
		setup_exec_signals();
		if(current->cmd)
			if (is_it_builtin(current->cmd, current, env) == 0)
				set_excode(env, create_child(current, env));
		current = current->next;
	}
	free_lst(msh);
	while (1)
		if (wait(NULL) < 0)
			break ;
	return (0);
}
// --------------------signals---------------------------

void signal_handler(int sig, siginfo_t *info, void *context)
{
	(void)sig;
	(void)info;
	(void)context;
	g_last_sig = SIGINT;
	rl_done = true;
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
	sa.sa_handler = SIG_IGN; // change this
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
        perror("sigaction failed for SIGQUIT");
        return (1);
    }
	return (0);
}

void	execute(t_msh *msh)
{
	t_msh	*current;

	current = msh;
	while (current)
	{
		printf("index: %d\n", current->index);
		if (current->cmd)
		{
			int	i = -1;
			while (current->cmd[++i])
				printf("cmd[%d]: %s\n", i, current->cmd[i]);
		}
		printf("heredoc: %d\n", current->here_doc);
		if (current->infile)
			printf("infile: %s\n", current->infile);
		if (current->outfile)
			printf("outfile: %s\n", current->outfile);
		current = current->next;
	}
}

void	set_global(t_env **env)
{
	if(g_last_sig == SIGQUIT)
		set_excode(env, 131);
	if(g_last_sig == SIGINT)
		set_excode(env, 130);
	g_last_sig = 0;
}

int	msh_loop(t_msh *msh, t_env **env)
{	
	char *line;
	char *prompt;

	while (1)
	{
		set_global(env);
		init_sigint();
		prompt = custom_prompt(env);
		if (!prompt)
			return (free_env(env), printf(RESET), 1);
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (g_last_sig != SIGINT || !ft_strlen(line))
		{
			add_history(line);
			msh = get_msh(line, *env);
			// execute(msh);
			exec(msh, env);
		}
	}
	return (0);
}

int	g_last_sig;

int main(void)
{
	t_msh msh;
	t_env **env = ft_calloc(sizeof(t_env **), 1);
	extern char **environ;

	if(!env)
		return (1);
	*env = env_into_list(environ);
	if(!*env)
		return (1);
	ft_bzero(&msh, sizeof(t_msh));
	msh_loop(&msh, env);
	free_env(env);
	return (0);
}
