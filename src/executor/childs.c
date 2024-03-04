#include "../../inc/minishell.h"

/* TODO: si hay algun outfile, no escribes en el pipe, escribes en el outfile */
void	first_child(t_msh *msh, int *fd, t_cmd *cmds)
{
	int		fd_in;
	int		fd_out;
	char	*path;

	msh->final_pid = fork();
	if (msh->final_pid == 0)
	{
		signals_here_doc();
		close(fd[0]);
		// printf("1)\n\t[] Pipe --> [%d]\n", fd[1]);
		fd_in = open_infile(cmds->infiles, cmds->infiles_count, -1);
		if (fd_in < 0)
			exit(1);
		fd_out = open_outfile(cmds->outfiles, cmds->outfiles_count, fd[1]);
		if (fd_out < 0)
			exit(1);
		path = get_path(cmds, msh->envp);
		if (!path)
			exit_malloc();
		// printf("\t[] Entrada final --> [%d]\n", fd_in);
		// printf("\t[] Salida final --> [%d]\n", fd_out);
		msh->cpy_last_in = dup2(fd_in, STDIN_FILENO);
		msh->cpy_last_out = dup2(fd_out, STDOUT_FILENO);
		if (fd_in != 0)
			close(fd_in);
		if (fd_out != 1 && fd_out != 2)
			close(fd_out);
		execve(path, cmds->complete_cmd, msh->envp);
		exit_execve(msh, cmds);
	}
	else if (msh->final_pid < 0)
		exit_fork_pipe(FORK);
}

void	mid_child(t_msh *msh, int *fd, int *new, t_cmd *cmds)
{
	char	*path;
	int		fd_in;
	int		fd_out;

	msh->final_pid = fork();
	if (msh->final_pid == 0)
	{
		signals_here_doc();
		printf("uwu\n");
		close(fd[1]);
		close(new[0]);
		fd_in = open_infile(cmds->infiles, cmds->infiles_count, fd[0]);
		if (fd_in < 0)
			exit(1);
		fd_out = open_outfile(cmds->outfiles, cmds->outfiles_count, new[1]);
		if (fd_out < 0)
			exit(1);
		path = get_path(cmds, msh->envp);
		if (!path)
			exit_malloc();
		msh->cpy_last_in = dup2(fd_in, STDIN_FILENO);
		msh->cpy_last_out = dup2(fd_out, STDOUT_FILENO);
		if (fd_in != 0)
			close(fd_in);
		if (fd_out != 1 && fd_out != 2)
			close(fd_out);
		execve(path, cmds->complete_cmd, msh->envp);
		exit_execve(msh, cmds);
	}
	else if (msh->final_pid < 0)
		exit_fork_pipe(FORK);
}

void	last_child(t_msh *msh, int *fd, t_cmd *cmds)
{
	int		fd_in;
	int		fd_out;
	char	*path;

	msh->final_pid = fork();
	if (msh->final_pid == 0)
	{
		signals_here_doc();
		close(fd[1]);
		fd_in = open_infile(cmds->infiles, cmds->infiles_count, fd[0]);
		if (fd_in < 0)
			exit(1);
		fd_out = open_outfile(cmds->outfiles, cmds->outfiles_count, -1);
		if (fd_out < 0)
			exit(1);
		path = get_path(cmds, msh->envp);
		if (!path)
			exit_malloc();
		msh->cpy_last_in = dup2(fd_in, STDIN_FILENO);
		msh->cpy_last_out = dup2(fd_out, STDOUT_FILENO);
		if (fd_in != 0)
			close(fd_in);
		if (fd_out != 1 && fd_out != 2)
			close(fd_out);
		execve(path, cmds->complete_cmd, msh->envp);
		exit_execve(msh, cmds);
	}
	else if (msh->final_pid < 0)
		exit_fork_pipe(FORK);
}
