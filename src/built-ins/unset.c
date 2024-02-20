#include "../../inc/minishell.h"

static int	search_var(t_msh *msh, char *aux)
{
	int	i;

	i = 0;
	while (msh->envp && msh->envp[i] != NULL)
	{
		if (!ft_strncmp(msh->envp[i], aux, ft_strlen(aux)))
			break ;
		i++;
	}
	return (i);
}

static int	search_valid_var(t_msh *msh, char *argument)
{
	int	i;

	i = 0;
	while (argument && argument[i] != '\0')
	{
		if (ft_correct_var_char(argument[i], MID_LETTER) != 1)
		{
			msh->last_out = 1;
			printf("uwu: unset: '%c': not a valid identifier\n", argument[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	remove_var(t_msh *msh, char *argument)
{
	int		i;
	char	*aux;

	if (search_valid_var(msh, argument) == 1)
		return ;
	aux = ft_strjoin(argument, "=");
	if (!aux)
		exit_malloc();
	if (!ft_strncmp(aux, "_=", 2))
	{
		free(aux);
		return ;
	}
	i = search_var(msh, aux);
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
			remove_var(msh, msh->cmds[nb_comand].arguments[i]);
			i++;
		}
	}
	return ;
}
