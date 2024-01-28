#include "../inc/minishell.h"

void	add_infile(t_file_type type, char *name, t_cmd *cmd, t_msh *msh)
{
	(void)msh;
	int			index;
	t_io_file	*new;

	new = ft_calloc(cmd->infiles_count + 1, sizeof(t_io_file));
	if (!new)
	{
		/* TODO: malloc error */
		return ;
	}

	/* Copiamos toda la info que teniamos a la nueva estructura */
	index = 0;
	while (index < cmd->infiles_count)
	{
		new[index].name = cmd->infiles[index].name;
		new[index].type = cmd->infiles[index].type;
		index++;
	}
	new[index].name = name;
	new[index].type = type;
	cmd->infiles_count++;

	/* Eliminamos la anterior lista y la actualizamos por la nueva */
	free(cmd->infiles);
	cmd->infiles = new;
}