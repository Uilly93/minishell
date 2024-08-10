/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:18:38 by wnocchi           #+#    #+#             */
/*   Updated: 2024/08/10 17:07:52 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_pipe(t_msh *msh, t_env **env)
{
	if (ft_lstlen(msh) > 1 || msh != ft_lastnode(msh))
	{
		if (pipe(msh->pipefd) == -1)
		{
			perror("msh: pipe:");
			set_excode(env, 129);
			return (1);
		}
	}
	return (0);
}

int	is_it_builtin(char **cmd, t_msh *msh, t_env **env)
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

int	create_child(t_msh *msh, t_env **env)
{
	pid_t	child;
	char	*path;

	child = fork();
	if (child == -1)
		perror("msh");
	else if (child == 0)
	{
		check_exec(msh->cmd[0], msh, env);
		path = join_path_access(msh->cmd[0], msh->env);
		if (!path)
			return (ft_printf(2, "msh: %s: command not found\n", msh->cmd[0]),
				free_env(env), free_lst(msh), exit(127), 127);
		if (redirect_fd(msh))
			return (free_env(env), free_lst(msh), free(path), exit(127), 1);
		if (execve(path, msh->cmd, (*env)->full_env) == -1)
		{
			perror("msh");
			return (free_env(env), free_lst(msh), free(path), exit(126), 1);
		}
	}
	return (0);
}

int	check_and_open(t_msh *msh)
{
	if (msh->here_doc == 1 && msh->infile != NULL)
		if (here_doc(msh) == SIGINT)
			return (SIGINT);
	if (msh->infile != NULL && msh->here_doc == 0)
	{
		msh->in = open(msh->infile, O_WRONLY, 0644);
		if (msh->in == -1)
		{
			set_excode(&msh->env, 1);
			return (perror("msh"), close_pipes(msh), close_files(msh), 1);
		}
		set_excode(&msh->env, 0);
	}
	if (msh->outfile != NULL)
	{
		msh->out = open(msh->outfile, get_flags(msh), 0644);
		if (msh->out == -1)
		{
			set_excode(&msh->env, 1);
			return (perror("msh"), close_pipes(msh), close_files(msh), 1);
		}
		set_excode(&msh->env, 0);
	}
	close_files(msh);
	return (0);
}

int	exec(t_msh *msh, t_env **env)
{
	t_msh	*current;

	current = msh;
	while (current)
	{
		if (check_and_open(current) != 0)
		{
			set_excode(env, 1);
			current = current->next;
			continue ;
		}
		if (init_pipe(current, env))
			break ;
		setup_exec_signals();
		if (current->cmd)
		{
			if (is_it_builtin(current->cmd, current, env) == 0)
				create_child(current, env);
		}
		current = current->next;
	}
	free_lst(msh);
	return (0);
}
