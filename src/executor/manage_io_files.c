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

static void	auxiliar_error_open(int *error, char *msg)
{
	perror(msg);
	*error = 1;
}

static int aux_open_infile(t_io_file infile, int *error)
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
	return (fd);
}

int	open_infile(t_io_file *infiles, int count, int pipe)
{
	int		i;
	int		fd;
	int		error;

	error = 0;
	i = 0;
	fd = -1;
	while (i < count)
	{
		fd = aux_open_infile(infiles[i], &error);
		if (i != count - 1)
		{
			close(fd);
			fd = -1;
		}
		i++;
	}
	if (error == 1)
	{
		if (fd > 0)
		{
			close(fd);
			fd = -1;
		}
		return (-1);
	}
	return (select_file(fd, pipe, STDIN_FILENO, count));
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
		if (outfiles[i].type == TRUNC)
			fd = open(outfiles[i].name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else
			fd = open(outfiles[i].name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
		{
			perror(outfiles[i].name);
			error = -1;
		}
		if (i != count - 1)
		{
			close(fd);
			fd = -1;
		}
		i++;
	}
	if (error == 1)
	{
		if (fd > 0)
		{
			close(fd);
			fd = -1;
		}
		return (-1);
	}
	return (select_file(fd, pipe, STDOUT_FILENO, count));
}
