#include "../inc/minishell.h"

void	*set_error(t_error error, t_msh *msh)
{
	if (msh)
		msh->error = error;
	return (NULL);
}

void	exit_malloc(void)
{
	perror(MALLOC_MSG);
	exit(1);
}

void	check_error(t_msh *msh)
{
	t_error error;

	error = msh->error;
	if (error == SYNTAX)
		printf(C_RED"\nmsh: syntax error\n"CLEAR);
	else if (error == CTR_D)
		printf(C_RED"\nmsh: syntax error: unexpected end of file\n"CLEAR);
	msh->error = NONE;
}

int		is_error(t_msh *msh)
{
	return (msh->error);
}