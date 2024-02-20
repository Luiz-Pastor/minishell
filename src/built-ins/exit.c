#include "../../inc/minishell.h"

int	check_if_nb(t_msh *msh, int nb_comand)
{
	int	i;

	i = 0;
	while (msh->cmds[nb_comand].arguments[0][i])
	{
		if (!ft_isdigit(msh->cmds->arguments[0][i]))
		{
			printf("msh: exit: %s: numeric argument required\n", \
				msh->cmds[nb_comand].arguments[0]);
			msh->last_out = 255;
			return (1);
		}
		i++;
	}
	return (0);
}

void	bd_exit(t_msh *msh, int nb_comand)
{
	printf("exit\n");
	msh->last_out = 1;
	if (matrix_length(msh->cmds[nb_comand].arguments) > 1)
	{
		msh->last_out = 1;
		printf("msh: exit: too many arguments\n");
		return ;
	}
	if (matrix_length(msh->cmds[nb_comand].arguments))
	{
		if (check_if_nb(msh, nb_comand) == 1)
			return ;
		else
		{
			msh->last_out = ft_atoi(msh->cmds[nb_comand].arguments[0]);
			if (msh->last_out > 255 || msh->last_out < 0)
				msh->last_out = msh->last_out % 256;
		}
	}
	exit(msh->last_out);
	return ;
}
