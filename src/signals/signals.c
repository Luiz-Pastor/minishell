#include "../../inc/minishell.h"

void	ctrl_4_manage(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("minishell> ");
	return ;
}

void	ctrl_c_manage(int sig)
{
	// tengo que ignorar la señal ctr c y hacer que se abra una nueva linea para escribir 
	(void)sig;
	// rl_replace_line("", 0);
	// printf("\n");
	// rl_on_new_line();
	// printf("minishell> ");
	// return ;
	exit(0);
}

void	signals_manage(t_msh *msh)
{
	(void)msh;

	/* Manear ctrl+c */
	signal(SIGINT, ctrl_c_manage);

	/* Manejar ctrl+4 // ctrl+/ */
	signal(SIGQUIT, ctrl_4_manage);
}