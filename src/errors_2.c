#include "../inc/minishell.h"

void	exit_execve(t_cmd *cmds)
{
	ft_putstr_fd("uwu: ", STDERR_FILENO);
	ft_putstr_fd(cmds->main, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(127);
}

void	error_export(char *arg)
{
	ft_putstr_fd("uwu: export: '", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

void	error_env(char *arg)
{
	ft_putstr_fd("uwu: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
}
