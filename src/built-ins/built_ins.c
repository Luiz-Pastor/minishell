#include "../../inc/minishell.h"

int	is_builtin(char *cmds)
{
	if (!ft_strcmp(cmds, "export"))
		return (1);
	else if (!ft_strcmp(cmds, "echo"))
		return (1);
	else if (!ft_strcmp(cmds, "env"))
		return (1);
	else if (!ft_strcmp(cmds, "pwd"))
		return (1);
	else if (!ft_strcmp(cmds, "cd"))
		return (1);
	else if (!ft_strcmp(cmds, "unset"))
		return (1);
	else if (!ft_strcmp(cmds, "exit"))
		return (1);
	return (0);
}

void	built_ins(t_msh *msh, int nb_comand)
{
	if (!ft_strcmp(msh->cmds[nb_comand].main, "export"))
		bd_export(msh, nb_comand);
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "echo"))
		bd_echo(msh, nb_comand);
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "env"))
		bd_env(msh);
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "pwd"))
		bd_pwd(msh);
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "cd"))
		bd_cd(msh, nb_comand);
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "unset"))
		bd_unset(msh, nb_comand);
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "exit"))
		bd_exit(msh, nb_comand);
	else
		return ;
}
