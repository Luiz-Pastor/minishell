#include "../../inc/minishell.h"

static void	ctrl_c_here(int sig)
{
	(void)sig;
	exit(0);
}

void	signals_here_doc(void)
{
	signal(SIGINT, ctrl_c_here);
}
