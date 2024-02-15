#include "../../inc/minishell.h"

void	ctrl_4_manage(int sig)
{
	(void)sig;
	return ;
}

void	ctrl_c_manage(int sig)
{
	// tengo que ignorar la señal ctr c y hacer que se abra una nueva linea para escribir 
	(void)sig;
	printf("no me mates pelotudo\n");
	exit(0);
}

void	signals_manage(t_msh *msh)
{
	(void)msh;
	/* TODO: esto no se ni lo que hace */

	// sigaction(SIGINT, NULL, &ctrl_c_manage);
	// signal(SIGINT, &ctrl_c_manage);
	signal(SIGQUIT, &ctrl_4_manage);
}