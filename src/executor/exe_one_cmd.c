#include "../../inc/minishell.h"

void	exe_built_ins(t_msh *msh)
{
	int	fd_in;
	int	fd_out;

	fd_in = open_infile(msh->cmds[0].infiles, msh->cmds[0].infiles_count);
	if (fd_in < 0)
	{
		msh->last_out = 1;
		return ; 
	}
	fd_out = open_outfile(msh->cmds[0].outfiles, msh->cmds[0].outfiles_count);
	if (fd_out < 0)
	{
		msh->last_out = 1;
		return ; 
	}
	msh->cpy_last_in = dup2(fd_in, STDIN_FILENO);
	msh->cpy_last_out = dup2(fd_out, STDOUT_FILENO);
	built_ins(msh, 0);
	dup2(msh->cpy_stdin, msh->cpy_last_in);
	dup2(msh->cpy_stdout, msh->cpy_last_out);
}

static void	child(t_cmd cmds, t_msh *msh)
{
	int		fd_in;
	int		fd_out;
	char	*path;

	fd_in = open_infile(cmds.infiles, cmds.infiles_count);
	if (fd_in < 0)
		exit (1);
	fd_out = open_outfile(cmds.outfiles, cmds.outfiles_count);
	if (fd_out < 0)
		exit (1);
	msh->cpy_last_in = dup2(fd_in, STDIN_FILENO);
	msh->cpy_last_out = dup2(fd_out, STDOUT_FILENO);
	path = get_path(&cmds, msh->envp);
	if (!path)
		exit_malloc();
	execve(path, cmds.complete_cmd, msh->envp);
	exit_execve(msh);
}

void	exe_one_cmd(t_msh *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_fork_pipe(FORK);
	if (pid == 0)
		child(msh->cmds[0], msh);
	waitpid(pid, &status, 0);
	msh->last_out = WEXITSTATUS(status);
}
