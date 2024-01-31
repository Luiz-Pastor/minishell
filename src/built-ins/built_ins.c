#include "../../inc/minishell.h"

void	built_ins(t_msh *msh, int nb_comand)
{
	if (!ft_strcmp(msh->cmds[nb_comand].main, "export"))
		bd_export(msh, nb_comand); /*TODO: enpezdo*/
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "echo"))
		bd_echo(msh, nb_comand); /*TODO: enpezdo*/
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "env"))
		bd_env(msh, nb_comand); /*TODO: enpezdo*/
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "pwd"))
		bd_pwd(msh, nb_comand); /*TODO: enpezdo*/
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "cd"))
		bd_cd(msh, nb_comand); /*TODO: sin empezar*/
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "unset"))
		bd_unset(msh, nb_comand); /*TODO: sin empezar*/
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "exit"))
		bd_exit(msh, nb_comand); /*TODO: sin empezar*/
	else
		return ;
}
