#include "../../inc/minishell.h"

void	bd_env(t_msh *msh, int nb_comand)
{
	int	index;

	if (msh->cmds[nb_comand].arguments != NULL)
	{
		error_env(msh->cmds[nb_comand].arguments[0]);
		return ;
	}
	msh->last_out = 0;
	index = 0;
	while (msh->envp[index])
		printf("%s\n", msh->envp[index++]);
}
