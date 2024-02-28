#include "../inc/minishell.h"

void	exit_execve(t_msh *msh, t_cmd *cmds)
{
	dup2(msh->cpy_stdout, msh->cpy_last_out);
	printf("uwu: %s: command not found\n", cmds->main);
	exit (127);
}
