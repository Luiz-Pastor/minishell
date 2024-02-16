#include "../../inc/minishell.h"

static void	one_command(t_msh *msh)
{
	if (is_builtin(msh->cmds[0].main))
	{
		/* Ejecutar el built-in */
		exe_built_ins(msh);
	}
    else
    {
		/* TODO: Ejecutar un comando alone */
		exe_one_cmd(msh);
        return ;
    }
}

int	executor(t_msh *msh)
{
	/* Miramos el numero de comandos que hay que ejecutar */
	if (msh->cmds_count == 1)
	{
		/* Solo ejecutamos un comando */
        one_command(msh);
        return (0);
	}
	else
	{
        return (0);
		/* Ejecutamos varios comandos */
	}
}