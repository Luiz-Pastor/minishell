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

void	exit_fork_pipe(t_error error)
{
	if (error == PIPE)
		perror(ERROR_PIPE_MSG);
	else if (error == FORK)
		perror(ERROR_FORK_MSG);
	exit(1);
}

void	check_error(t_msh *msh)
{
	t_error error;

	error = msh->error;
	if (error == SYNTAX)
		printf("uwu: syntax error near unexpected token\n");
	else if (error == CTR_D)
		printf("uwu: syntax error: unexpected end of file\n");
	msh->error = NONE;
}

int		is_error(t_msh *msh)
{
	return (msh->error);
}

void	exit_execve(t_msh *msh, t_cmd *cmds)
{
	dup2(msh->cpy_stdout, msh->cpy_last_out);
	printf("uwu: %s: command not found\n", cmds->main);
	exit (127);
}
