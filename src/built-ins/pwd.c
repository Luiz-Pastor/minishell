#include "../../inc/minishell.h"

void	*bd_pwd(t_msh *msh, int nb_comand)
{
	(void)nb_comand; // quitar no vale pa nah y hacerla void
	(void)msh;
	// se la pea los argumentos que hayya uwu
	
	printf("%s\n", getcwd(NULL, 0));
	return (NULL);
}