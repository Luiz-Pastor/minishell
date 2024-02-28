#include "../../inc/minishell.h"

#include <termios.h>

void	ctrl_c_disable(void)
{
	struct termios	termios;

	if (tcgetattr(0, &termios) != 0)
	{
		perror("uwu: tcgetattr error\n");
		exit (1);
	}
	termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &termios) != 0)
	{
		perror("uwu: tcsetattr error\n");
		exit (1);
	}
}

void	ctrl_4_manage(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	ctrl_c_manage(int sig)
{
	(void)sig;
	if (signal_control == 0)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		write(STDERR_FILENO, "\n", 1);
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

// void	signal_ctlc_heredoc(int sig)
// {
// 	if (sig == SIGINT)
// 		close(STDIN_FILENO);
// 	exit(0);
// }
