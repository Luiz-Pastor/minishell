#include "../../inc/minishell.h"

void	bd_env(t_msh *msh, int nb_comand)
{
	int	index;
	(void)nb_comand;

	index = 0;
	while (msh->envp[index])
		printf("%s\n", msh->envp[index++]);
}