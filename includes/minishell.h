/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 09:48:36 by wnocchi           #+#    #+#             */
/*   Updated: 2024/05/30 13:55:58 by wnocchi          ###   ########.fr       */
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
	char 	*hlimit;
	char	**prompt;
	int		nb_cmd;
	int		out;
	int		in;
	char	*infile;
	char	*outfile;
}	t_msh;

int		check_heredoc(t_msh *msh, char **av);
void	here_doc(t_msh *msh, char **av);
void	ft_echo(char **cmd);
int		ft_cd(char **arg);
int		get_pwd(char **arg);
int		export_env(char *arg, char **envp);

#endif