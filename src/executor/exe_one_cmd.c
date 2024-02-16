#include "../../inc/minishell.h"

void	exe_built_ins(t_msh *msh)
{
	int	fd_in;
	int	fd_out;

	/* Nos quedamos con el infile y el outfile que necesitamos */
	fd_in = open_infile(msh->cmds[0].infiles, msh->cmds[0].infiles_count);
	if (fd_in < 0)
		return ;
	fd_out = open_outfile(msh->cmds[0].outfiles, msh->cmds[0].outfiles_count);
	if (fd_out < 0)
		return ;
	
	/* Rederigimos la entrada y la salida  */
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);

	/* Ejecutamos el built-in*/
	built_ins(msh, 0);

	/* Volvemos a rederigir la entrada y salida */
	dup2(STDIN_FILENO, fd_in);
	dup2(STDOUT_FILENO, fd_out);
}

void	child(t_cmd cmds, char **envp)
{
	int		fd_in;
	int		fd_out;
	char	*path;

	fd_in = open_infile(cmds.infiles, cmds.infiles_count);
	if (fd_in < 0)
		return ;
	fd_out = open_outfile(cmds.outfiles, cmds.outfiles_count);
	if (fd_out < 0)
		return ;
	path = get_path(&cmds, envp);
	
	execve();
}
void	exe_one_cmd(t_msh *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		exit_fork_pipe(FORK);
	if (pid == 0)
		child(msh->cmds[0], msh->envp);
	waitpid(pid, &status, 0);
	msh->last_out = WEXITSTATUS(status);
}