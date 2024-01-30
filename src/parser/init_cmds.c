#include "../../inc/minishell.h"

void	*create_commands(t_msh *msh)
{
	msh->cmds = ft_calloc(msh->cmds_count, sizeof(t_cmd));
	return (msh->cmds);
}

void	*delete_commands(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	while (msh && msh->cmds && i < msh->cmds_count)
	{
		j = -1;
		/* Eliminamos el infile y el outfile */
		while (msh->cmds[i].infiles && ++j < msh->cmds[i].infiles_count)
			ft_mfree(2, &msh->cmds[i].infiles[j].name, &msh->cmds[i].infiles[j]);
		j = -1;
		while (msh->cmds[i].outfiles && ++j < msh->cmds[i].outfiles_count)
			ft_mfree(2, &msh->cmds[i].outfiles[j].name, &msh->cmds[i].outfiles[j]);
		
		/* Eliminamos el comando y argumentos */
		free(msh->cmds[i].main);
		free_parts(NULL, msh->cmds[i].input);
		j = -1;
		while (msh->cmds[i].arguments && msh->cmds[i].arguments[++j])
			free(msh->cmds[i].arguments[j]);
	}
	free(msh->cmds);
	return (NULL);
}