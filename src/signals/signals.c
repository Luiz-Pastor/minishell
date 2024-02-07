#include "../../inc/minishell.h"

void	ctrl_d_manage(int sig)
{
	(void)sig;
	return ;
}

void	ctrl_c_manage(int sig)
{
	(void)sig;
	return ;
}

void	signals_manage(t_msh *msh)
{
	(void)msh;
	/* TODO: esto no se ni lo que hace */
	signal(SIGINT, &ctrl_c_manage);
	signal(SIGQUIT, &ctrl_d_manage);
}