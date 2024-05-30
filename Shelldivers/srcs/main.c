/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsiefert <nsiefert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 08:18:21 by nate              #+#    #+#             */
/*   Updated: 2024/05/02 05:38:37 by nsiefert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_custompwd(t_data *data)
{
	int		i;
	char	*pwd;

	i = -1;
	pwd = ft_strjoin("", &data->ms_env[1][0]);
	while(data->ms_env[1][++i])
	{
		if (data->ms_env[1][i] == "/" && data->ms_env[1][i + 1])
		{
			pwd = ft_strjoin(pwd, "/");
			pwd = ft_strjoin(pwd, &data->ms_env[1][i + 1]);
		}
	}
	return (pwd);
}

// Launch Shell 
// 1. Print the shell prompt
// 2. Read the input
// 3. If the input is NULL, break
// 4. If the input is not NULL, check if the input is in the history
// 5. If the input is in the history, continue to the next iteration
// 6. If the input is not in the history, launch the lexer
// 7. If the lexer returns 0, print an error message
// 8. Wait for the child process to finish
// 9. Initialize the signals
// 10. Free the input
void	launch_shell(t_data *data, char *str, pid_t pid)
{
	while (1)
	{
		if (ms_sig.exit_status == 1)
			ft_printf("ShellDivers %s \033[32m ↪ \033[0m", ft_custompwd(data));
		else 
			ft_printf("ShellDivers %s \033[31m ↪ \033[0m", ft_custompwd(data));
		str = readline(" : \n");
		if (!str)
			break;
		else
		{
			if (history(str) == 0)
				pid = lexer(str, data);
			if (pid == 0)
				ft_error_free("PID error", data, 2);
			waitpid(pid, NULL, 0);
			sig_init(1);
			free(str);
		}
	}
}

// 1. Create env
// 2. Launch shell
int main(int ac, char **av, char **envp)
{
	pid_t	pid;
	char	*str;
	t_data 	*data;

	(void) ac;
	(void) av;
	pid = 1;
	str = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		ft_error("Malloc data !");
	data = do_env(envp, data, str);
	launch_shell(data, str, pid);
}
