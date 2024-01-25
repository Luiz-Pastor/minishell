#include "../../inc/minishell.h"

void	bd_pwd(t_msh *data)
{
	return (getcwd(NULL, 0));
}