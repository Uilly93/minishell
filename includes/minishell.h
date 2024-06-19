/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:48:36 by wnocchi           #+#    #+#             */
/*   Updated: 2024/06/19 15:49:31 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <errno.h>
# include <signal.h>

typedef struct s_msh
{
	char 			*hlimit;
	char			**prompt;
	char			**cmd;
	int				in;
	int				out;
	char			*infile;
	char			*outfile;
	int				index;
	struct s_msh	*next;
}	t_msh;

int		check_heredoc(t_msh *msh, char **av);
void	here_doc(t_msh *msh, char **av);
void	ft_echo(char **cmd);
int		ft_cd(char **arg);
int		get_pwd(char **arg);
int		export_env(char *arg, char **envp);
int		redirect_fd(t_msh *msh, int *pipefd);
int		close_fds(int *pipefd, t_msh *msh);
int		redirect_fd_write(t_msh *msh, int *pipefd);
int		ft_lstlen(t_msh *msh);
void	ft_free(void *ptr);
char	*join_path_access(char *av, char **envp);
char	**get_path(char **envp);
int		create_child(t_msh *msh, int *pipefd, char **envp, char *av); // enfant qui lis dans un infile


#endif