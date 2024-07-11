/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:48:36 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/11 16:31:59 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <errno.h>
# include <signal.h>

typedef struct s_env
{
	char	*full_var;
	char	*var_name;
	char	*var;
	bool	set;
	// char **cpy; //sort and print;
	struct	s_env	*next;
} t_env;

typedef struct s_msh
{
	char 			*hlimit;
	// char			**prompt;
	char			**cmd;
	char			**my_env;
	int				in;
	int				out;
	bool			out_appen;
	char			*infile;
	char			*outfile;
	int				index;
	int				pipefd[2];
	struct s_env	*env;
	struct s_msh	*next;
	struct s_msh	*prev;
}	t_msh;


int	split_env(t_env *env);
int is_equal(char *var);
char *get_var_name(char *var);
char *get_var(char *var);
int		ft_env(t_env *env, t_msh *msh);
// int		check_heredoc(t_msh *msh, char **av);
void	here_doc(t_msh *msh, char **av);
void	ft_echo(t_msh *msh);
int		ft_cd(char **arg, char **envp);
int		ft_exit(t_msh *msh);
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
char	*join_path_access(char *av, char **envp);
char	**get_path(char **envp);
void	ft_err(char *error);
int		init_sigint();
char	**get_env(t_env *env);
void	signal_handler(int sig, siginfo_t *info, void *context);
void	free_lst(t_msh *msh);

#endif