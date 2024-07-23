#include "minishell.h"

void	cmd_echo(int ac, char **av)
{
	int	i;
	int	nl;

	i = 0;
	nl = 1;
	if (ac > 1 && !ft_strncmp(av[1], "-n", 2))
	{
		i++;
		nl = 0;
	}
	while (av[++i])
	{
		ft_printf("%s", av[i]);
		if (i != ac)
			ft_printf(" ");
	}
	if (nl)
		ft_printf("\n");
}

void	cmd_cd(int ac, char **av)
{
	if (ac > 2)
	{
		perror("cd");
		return ;
	}
	if (chdir(av[1]))
		perror("cd");
}

void	cmd_pwd(int ac, char **av)
{
	char	*cwd;

	(void)ac;
	(void)av;
	cwd = malloc(PATH_MAX + 1);
	if (!cwd)
		return ;
	if (getcwd(cwd, PATH_MAX))
		ft_printf("%s\n", cwd);
	else
		perror("pwd");
	free(cwd);
}

void	cmd_export(int ac, char **av)
{
	(void)ac;
	(void)av;
}

void	cmd_unset(int ac, char **av)
{
	(void)ac;
	(void)av;
}

void	cmd_env(int ac, char **av)
{
	extern char	**environ;
	int			i;

	if (ac > 1)
	{
		perror("env");
		return ;
	}
	(void)av;
	i = -1;
	while (environ[++i])
		ft_printf("%s\n", environ[i]);
}

int	is_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

void	cmd_exit(int ac, char **av)
{
	int	code;

	if (ac > 2)
	{
		perror("exit");
		return ;
	}
	ft_printf("exit\n");
	if (av[1])
	{
		if (is_numeric(av[1]))
			exit(ft_atoi(av[1]));
		else
			perror("exit");	
	}
	exit(0);
}

void	builtins(int ac, char **av)
{
	char	*cmd;

	cmd = av[0];
	if (!ft_strncmp(cmd, "echo", 5))
		cmd_echo(ac, av);
	else if (!ft_strncmp(cmd, "cd", 3))
		cmd_cd(ac, av);
	else if (!ft_strncmp(cmd, "pwd", 4))
		cmd_pwd(ac, av);
	else if (!ft_strncmp(cmd, "export", 7))
		cmd_export(ac, av);
	else if (!ft_strncmp(cmd, "unset", 6))
		cmd_unset(ac, av);
	else if (!ft_strncmp(cmd, "env", 4))
		cmd_env(ac, av);
	else if (!ft_strncmp(cmd, "exit", 5))
		cmd_exit(ac, av);
}
