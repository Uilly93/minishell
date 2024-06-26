/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:48:36 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/27 16:59:12 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <readline/readline.h>
# include <errno.h>
# include <signal.h>


typedef struct s_msh
{
	char 			*hlimit;
	// char			**prompt;
	char			**cmd;
	int				in;
	int				out;
	bool			out_appen;
	char			*infile;
	char			*outfile;
	int				index;
	int				pipefd[2];
	struct s_msh	*next;
	struct s_msh	*prev;
}	t_msh;

// int		check_heredoc(t_msh *msh, char **av);
void	here_doc(t_msh *msh, char **av);
void	ft_echo(t_msh *msh);
int		ft_cd(char **arg, char **envp);
int		get_pwd(char **arg, t_msh *msh);
int		export_env(char *arg, char **envp);
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
int		create_child(t_msh *msh, int *pipefd, char **envp, char *av); // enfant qui lis dans un infile


#endif