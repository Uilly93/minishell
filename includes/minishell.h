/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:48:36 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/24 15:18:06 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <errno.h>
# include <signal.h>
// # include "parsing.h"

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
	char 			*hlimit;
	// char			**prompt;
	int				here_doc;
	char			**cmd;
	char			**my_env;
	int				in;
	int				out;
	int				append;
	char			*infile;
	char			*outfile;
	int				index;
	int				pipefd[2];
	struct s_env	*env;
	struct s_msh	*next;
	struct s_msh	*prev;
}	t_msh;

// void	ft_addnode(t_msh **lst, t_msh *add);
int	split_env(t_env *env);
int is_equal(char *var);
char *get_key_env(char *var);
char *get_value_env(char *var);
int	env_len(t_env *env);
int	update_env(t_env *env);
int		ft_env(t_env *env, t_msh *msh);
int	ft_unset(t_env **env, char **av);
int	ft_del_node(t_env **head, char *av);
// int		check_heredoc(t_msh *msh, char **av);
void	here_doc(t_msh *msh, char **av);
void	ft_echo(t_msh *msh);
int		ft_cd(char **arg, t_env *env);
int		ft_exit(t_msh *msh, t_env *env);
int		get_pwd(char **arg, t_msh *msh);
int		ft_export(t_msh *msh, t_env *env);
int		free_env(t_env *env);
t_env *env_into_list(char **envp);
// int		export_env(char *arg, char **envp);
t_msh	*ft_lastnode(t_msh *lst);
int		redirect_fd(t_msh *msh);
int		which_fd(t_msh *msh);
int		close_pipes(t_msh *msh);
int		close_files(t_msh *msh);
void	free_tab(char **tab);
int		get_flags(t_msh *msh);
int		redirect_fd_write(t_msh *msh, int *pipefd);
int		ft_lstlen(t_msh *msh);
void	ft_free(void *ptr);
char	*join_path_access(char *av, t_env *env);
char	**get_path(t_env *env);
void	ft_err(char *error);
int		init_sigint();
char	**get_env(t_env *env);
void	signal_handler(int sig, siginfo_t *info, void *context);
void	free_lst(t_msh *msh);

t_env	*create_env(char *key, char *value);
void	split_key_value(char *str, char **key, char **value);
void	env_add_back(t_env **env, t_env *add);
t_msh	*get_msh(char *line, t_env *env);
// void	free_env(t_env **env);
// t_env	*get_env(void);
// char    *get_value_parsing(t_env *env, char *key);

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

t_msh	*create_msh(int index, t_env *env);
int		count_words(t_token *token);
t_msh	*msh_get_last(t_msh *msh);
void	msh_add_back(t_msh **msh, t_msh *add);
void	free_msh(t_msh **msh);
void	fill_command(t_msh *msh, t_token **token);
void	fill_smaller(t_msh *msh, t_token **token);
void	fill_bigger(t_msh *msh, t_token **token);
void	fill_msh(t_msh *msh, t_token **token);
t_msh	*parsing(t_token *token, t_env *env);
// char	*get_value(char *value);

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