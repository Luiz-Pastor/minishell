#include "../../inc/minishell.h"

void	bd_echo(t_msh *msh, int nb_comand)
{
	int	i;

	i = 0;
	if (msh->cmds[nb_comand].arguments == NULL)
	{
		printf("\n");
		return ;
	}
	else if (msh->cmds[nb_comand].arguments != NULL)
	{
		if (!ft_strcmp(msh->cmds[nb_comand].arguments[0], "-n"))
		{
			i++;
			if (!msh->cmds[nb_comand].arguments[i])
				return ;
			else
			{
				while (msh->cmds[nb_comand].arguments[i])
				{
					printf("%s", msh->cmds[nb_comand].arguments[i]);
					if (msh->cmds[nb_comand].arguments[i + 1] != NULL)
					printf(" ");
					i++;
				}
			}
		}
		else
		{
			while (msh->cmds[nb_comand].arguments[i])
			{
				printf("%s", msh->cmds[nb_comand].arguments[i]);
				if (msh->cmds[nb_comand].arguments[i + 1] != NULL)
					printf(" ");
				i++;
			}
			printf("\n");
		}
	}
	return ;
}
