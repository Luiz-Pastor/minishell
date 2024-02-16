#include "../../inc/minishell.h"

int	open_infile(t_io_file *infiles, int count)
{
	int		i;
	int		fd;
	char	*name;

	i = 0;
	if (count == 0)
		return (STDIN_FILENO);
	while (i < count)
	{
		if (infiles[i].type == INFILE)
		{
			fd = open(infiles[i].name, O_RDONLY);
			if (fd < 0)
				perror(infiles[i].name);
		}
		else
		{
			name = here_doc(infiles[i].name);
			if (!name)
				perror(infiles[i].name);
			fd = open(name, O_RDONLY);
			if (fd < 0)
				perror(name);
		}
		if (i != count - 1)
			close(fd);
		i++;
	}
	return (fd);
}

int	open_outfile(t_io_file *outfiles, int count)
{
	int	i;
	int	fd;

	i = 0;
	if (count == 0)
		return (STDOUT_FILENO);
	while (i < count)
	{
		if (outfiles[i].type == TRUNC)
			fd = open(outfiles[i].name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else
			fd = open(outfiles[i].name, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (fd < 0)
			perror(outfiles[i].name);
		if (i != count - 1)
			close(fd);
		i++;
	}
	return (fd);
}