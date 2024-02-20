#include "../../inc/minishell.h"

static void	remove_var(t_msh *msh, char *argument)
{
	int		i;
	char	*aux;

	aux = ft_strjoin(argument, "=");
	if (!aux)
		exit_malloc();
	if (!ft_strncmp(aux, "_=", 2))
	{
		free(aux);
		return ;
	}
	i = 0;
	while (msh->envp[i] != NULL)
	{
		if (!ft_strncmp(msh->envp[i], aux, ft_strlen(aux)))
			break ;
		i++;
	}
	free(aux);
	if (msh->envp[i] == NULL)
		return ;
	free(msh->envp[i]);
	while (msh->envp[i] != NULL)
	{
		msh->envp[i] = msh->envp[i + 1];
		i++;
	}
}

void	bd_unset(t_msh *msh, int nb_comand)
{
	int	i;

	i = 0;
	if (msh->cmds[nb_comand].arguments != NULL)
	{
		while (msh->cmds[nb_comand].arguments[i] != NULL)
		{
			/* TODO: maybe hay que ver si los caracteres del unset puden ser variables y en el caso de que no devolver error*/
			/* si son */
			remove_var(msh, msh->cmds[nb_comand].arguments[i]);
			i++;
		}
	}
	return ;
}
