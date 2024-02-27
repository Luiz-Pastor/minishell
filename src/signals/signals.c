#include "../../inc/minishell.h"

// #include <termios.h>

void	ctrl_4_manage(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("UwUshell> ");
	return ;
}

// void	ctrl_c_manage(int sig)
// {
// 	// tengo que ignorar la señal ctr c y hacer que se abra una nueva linea para escribir 
// 	(void)sig;
// 	tputs("uwu\n");
// 	// rl_on_new_line();
// 	// rl_replace_line("\n", 0);
// 	// rl_redisplay();
// 	// printf("\n");
// }

void	ctrl_c_manage(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_manage(t_msh *msh)
{
	(void)msh;

	/* Manear ctrl+c */
	signal(SIGINT, ctrl_c_manage);

	/* Manejar ctrl+4 // ctrl+/ */
	signal(SIGQUIT, ctrl_4_manage);
}

void	signal_ctlc_heredoc(int sig)
{
	if (sig == SIGINT)
		close(STDIN_FILENO);
	exit(0);
}
