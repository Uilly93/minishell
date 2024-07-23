/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:15:54 by tchalaou          #+#    #+#             */
/*   Updated: 2024/07/23 15:38:36 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <limits.h>

# define WORD 1
# define SMALLER 2
# define BIGGER 3
# define PIPE 4

typedef struct s_env
{
	char	**full_env;
	char	*full_var;
	char	*key;
	char	*value;
	struct	s_env	*next;
} t_env;

typedef struct s_token
{
	int		id;
	char		*word;
	t_env		*env;
	struct s_token	*next;
}		t_token;

typedef struct s_msh
{
	int		index;
	char	**cmd;
	char	*infile;
	char	*outfile;
	int		here_doc;
	int		append;
	int		in_fd;
	int		out_fd;
	int		pipefd[2];
	struct s_msh	*next;
	struct s_msh	*prev;
}		t_msh;

t_env	*create_env(char *key, char *value);
void	split_key_value(char *str, char **key, char **value);
void	env_add_back(t_env **env, t_env *add);
void	free_env(t_env **env);
t_env	*get_env(void);
char    *get_value(t_env *env, char *key);

t_token	*create_token(t_env *env);
int		is_whitespace(char c);
int		word_len(char *line, int start);
void	token_add_back(t_token **token, t_token *add);
void	free_token(t_token **token);
void	fill_word(t_token *token, char *line, int *i);
void	fill_quote(t_token *token, char *line, int *i);
void	fill_doublequote(t_token *token, char *line, int *i);
void    fill_value(t_token *token, char *line, int *i);
void	fill_token(t_token *token, char *line, int *i);
t_token	*lexing(char *line, t_env *env);

t_msh	*create_msh(int index);
int		count_words(t_token *token);
t_msh	*msh_get_last(t_msh *msh);
void	msh_add_back(t_msh **msh, t_msh *add);
void	free_msh(t_msh **msh);
void	fill_command(t_msh *msh, t_token **token);
void	fill_smaller(t_msh *msh, t_token **token);
void	fill_bigger(t_msh *msh, t_token **token);
void	fill_msh(t_msh *msh, t_token **token);
t_msh	*parsing(t_token *token);

int		array_size(char **array);
void	free_array(char **array);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);

void	execute(t_msh *msh);

void	builtins(int ac, char **av);
void	cmd_echo(int ac, char **av);
void	cmd_cd(int ac, char **av);
void	cmd_pwd(int ac, char **av);
void	cmd_export(int ac, char **av);
void	cmd_unset(int ac, char **av);
void	cmd_env(int ac, char **av);
void	cmd_exit(int ac, char **av);

#endif
