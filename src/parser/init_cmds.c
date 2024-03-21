/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:29 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:30 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*create_commands(t_msh *msh)
{
	msh->cmds = ft_calloc(msh->cmds_count, sizeof(t_cmd));
	return (msh->cmds);
}

static void	delete_io_files(t_io_file *file)
{
	free(file->name);
	free(file);
}

void	*delete_commands(t_msh *msh)
{
	int	i;
	int	j;

	i = 0;
	while (msh && msh->cmds && i < msh->cmds_count)
	{
		j = -1;
		while (msh->cmds[i].infiles && ++j < msh->cmds[i].infiles_count)
			delete_io_files(&msh->cmds[i].infiles[j]);
		j = -1;
		while (msh->cmds[i].outfiles && ++j < msh->cmds[i].outfiles_count)
			delete_io_files(&msh->cmds[i].outfiles[j]);
		free(msh->cmds[i].main);
		free_parts(NULL, msh->cmds[i].input);
		j = -1;
		while (msh->cmds[i].arguments && msh->cmds[i].arguments[++j])
			free(msh->cmds[i].arguments[j]);
	}
	free(msh->cmds);
	return (NULL);
}
