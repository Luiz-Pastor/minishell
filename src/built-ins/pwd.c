#include "../../inc/minishell.h"

void	*bd_pwd(t_msh *msh)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	msh->last_out = 0;
	return (NULL);
}
