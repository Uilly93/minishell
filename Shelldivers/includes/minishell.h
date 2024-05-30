/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsiefert <nsiefert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:18:48 by nate              #+#    #+#             */
/*   Updated: 2024/05/02 04:37:22 by nsiefert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*\ -- INCLUDES -- */

# include "../libft/include/libft.h"
# include "defines.h"

# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>

/*\ -- STRUCTURES -- \*/

// Contient :
// L'environnement minimal pour faire tourner le shell
typedef struct s_data
{
	char	**ms_env;

}	t_data;

// Contient :
// cmd = [0] - Commande || [1] - Options || [2] - Arguments
// in = input
// out = output
// next = commande suivante
typedef struct s_cmds
{
	char			**cmd;
	char			**in;
	char			**out;
	struct s_cmds	*next;
}	t_cmds;

// Contient les signaux pour communiquer les sorties
typedef struct s_sig
{
	int				sigquit;
	int				sigint;
	unsigned char	exit_status;
	pid_t			pid;
	int				checker;
}	t_sig;

/*\ -- PROTOTYPES -- \*/

t_data	*do_env(char **envp, t_data *data, char *str);
void    ft_error(char *str);
pid_t   lexer(char *str, t_data *data);

/*\ -- History -- \*/
int		history(char *str);

extern t_sig	ms_sig;
#endif