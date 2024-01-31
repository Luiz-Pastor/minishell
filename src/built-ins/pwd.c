#include "../../inc/minishell.h"

void	*bd_pwd(t_msh *msh, int nb_comand)
{
	(void)nb_comand;
	(void)msh;
	
	return (getcwd(NULL, 0));
}