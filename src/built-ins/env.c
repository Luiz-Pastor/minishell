#include "../../inc/minishell.h"

void	bd_env(t_msh *msh)
{
	int	index;

	msh->last_out = 0;
	index = 0;
	while (msh->envp[index])
		printf("%s\n", msh->envp[index++]);
}
