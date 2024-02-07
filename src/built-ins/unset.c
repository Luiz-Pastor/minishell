#include "../../inc/minishell.h"

void	remove_var(t_msh *msh, char *argument, int nb_comand)
{
	int		i;
	char	*aux;

	aux = ft_strjoin(argument, "=");
	if (!aux)
		return ;
	i = 0;
	(void)nb_comand;
	if (!ft_strncmp(argument, "_", 1))
		return ;
	while (msh->envp[i] != NULL)
	{
		if (!ft_strncmp(msh->envp[i], aux, ft_strlen(aux)))
			break ;
		i++;
	}
	if (msh->envp[i] == NULL)
		return ;
	while (msh->envp[i] != NULL)
	// la ultima posicion que seria NULL se meteria en la anterior? crasheari?¿?
	{
		msh->envp[i] = msh->envp[i + 1];
		i++;
	}
}

void	bd_unset(t_msh *msh, int nb_comand)
{
	int	i;

	i = 0;
	if (!ft_strcmp(msh->cmds[nb_comand].main, "unset")
		&& msh->cmds[nb_comand].arguments != NULL)
	{
		while (msh->cmds[nb_comand].arguments[i] != NULL)
		{
			remove_var(msh, msh->cmds[nb_comand].arguments[i], nb_comand);
			i++;
		}
	}
	return ;
}
