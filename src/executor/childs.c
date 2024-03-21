/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:48 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:49 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_aux(t_msh *msh, t_cmd *cmds, int fd_in, int fd_out)
{
	char	*path;

	path = get_path(cmds, msh->envp);
	if (!path)
		exit_malloc();
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1 && fd_out != 2)
		close(fd_out);
	if (is_builtin(cmds->main) == 1)
		built_ins(msh, cmds->nb);
	else
	{
		execve(path, cmds->complete_cmd, msh->envp);
		exit_execve(cmds);
	}
	exit(msh->last_out);
}

void	first_child(t_msh *msh, int *fd, t_cmd *cmds)
{
	int	fd_in;
	int	fd_out;

	msh->final_pid = fork();
	if (msh->final_pid == 0)
	{
		signals_here_doc();
		close(fd[0]);
		fd_in = open_infile(cmds->infiles, cmds->infiles_count, -1);
		if (fd_in < 0)
			exit(1);
		fd_out = open_outfile(cmds->outfiles, cmds->outfiles_count, fd[1]);
		if (fd_out < 0)
			exit(1);
		child_aux(msh, cmds, fd_in, fd_out);
	}
	else if (msh->final_pid < 0)
		exit_fork_pipe(FORK);
}

void	mid_child(t_msh *msh, int *fd, int *new, t_cmd *cmds)
{
	int	fd_in;
	int	fd_out;

	msh->final_pid = fork();
	if (msh->final_pid == 0)
	{
		signals_here_doc();
		close(new[0]);
		fd_in = open_infile(cmds->infiles, cmds->infiles_count, fd[0]);
		if (fd_in < 0)
			exit(1);
		fd_out = open_outfile(cmds->outfiles, cmds->outfiles_count, new[1]);
		if (fd_out < 0)
			exit(1);
		child_aux(msh, cmds, fd_in, fd_out);
	}
	else if (msh->final_pid < 0)
		exit_fork_pipe(FORK);
}

void	last_child(t_msh *msh, int *fd, t_cmd *cmds)
{
	int	fd_in;
	int	fd_out;

	msh->final_pid = fork();
	if (msh->final_pid == 0)
	{
		signals_here_doc();
		fd_in = open_infile(cmds->infiles, cmds->infiles_count, fd[0]);
		if (fd_in < 0)
			exit(1);
		fd_out = open_outfile(cmds->outfiles, cmds->outfiles_count, -1);
		if (fd_out < 0)
			exit(1);
		child_aux(msh, cmds, fd_in, fd_out);
	}
	else if (msh->final_pid < 0)
		exit_fork_pipe(FORK);
}
