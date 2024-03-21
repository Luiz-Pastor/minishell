/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_io_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:54 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:55 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	select_file(int input, int pipe, int predetermined, int count)
{
	if (input > 0)
	{
		if (pipe > 0)
			close(pipe);
		return (input);
	}
	if (pipe > 0)
		return (pipe);
	if (count == 0)
		return (predetermined);
	return (-1);
}

static int	aux_open_infile(t_io_file infile, int i, int count, int *error)
{
	int		fd;
	char	*name;

	if (infile.type == INFILE)
	{
		fd = open(infile.name, O_RDONLY);
		if (fd < 0)
			auxiliar_error_open(error, infile.name);
	}
	else
	{
		name = here_doc(infile.name);
		if (!name)
			exit_malloc();
		fd = open(name, O_RDONLY);
		if (fd < 0)
			auxiliar_error_open(error, name);
		free(name);
	}
	if (i != count - 1)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}

int	open_infile(t_io_file *infiles, int count, int pipe)
{
	int	i;
	int	fd;
	int	error;

	error = 0;
	i = 0;
	fd = -1;
	while (i < count)
	{
		fd = aux_open_infile(infiles[i], i, count, &error);
		i++;
	}
	if (error == 1)
	{
		if (fd > 0)
		{
			close(fd);
			if (pipe > 0)
				close(pipe);
			fd = -1;
		}
		return (-1);
	}
	return (select_file(fd, pipe, STDIN_FILENO, count));
}

static int	aux_open_outfile(t_io_file *outfiles, int i, int count, int *error)
{
	int	fd;

	fd = -1;
	if (outfiles[i].type == TRUNC)
		fd = open(outfiles[i].name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		fd = open(outfiles[i].name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd < 0)
	{
		perror(outfiles[i].name);
		*error = -1;
	}
	if (i != count - 1)
	{
		close(fd);
		fd = -1;
	}
	i++;
	return (fd);
}

int	open_outfile(t_io_file *outfiles, int count, int pipe)
{
	int	i;
	int	fd;
	int	error;

	error = 0;
	i = 0;
	fd = -1;
	while (i < count)
	{
		fd = aux_open_outfile(outfiles, i, count, &error);
		i++;
	}
	if (error == 1)
	{
		if (fd > 0)
		{
			close(fd);
			if (pipe > 0)
				close(pipe);
			fd = -1;
		}
		return (-1);
	}
	return (select_file(fd, pipe, STDOUT_FILENO, count));
}
