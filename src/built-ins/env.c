#include "../../inc/minishell.h"

void	bd_env(t_msh *data)
{
	int	index;

	index = 0;
	while (data->envp[index])
		printf("%s\n", data->envp[index++]);
}