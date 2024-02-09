#include "../../inc/minishell.h"

/* UN COMANDO
Cosas a mirar para cada comando:
	Crear un proceso hijo y:
		- Abrir todos los infiles
		- Abrimos todos los outfiles
		- Sacar la ruta del comando
		- Juntar comando con argumentos
		- Hacer los dups
		- Hacer execve

Cosas a mirar en los build-ins
	- Abrimos los infiles
	- Abrimos los outfiles
	- Hacemos dup2
	- Ejecutamos built-in
	- Hacemos dup2 para volver a entrada y salida estandar
*/

static void	one_command(t_msh *msh)
{
	if (is_builtin(msh->cmds[0]))
	{
		/* TODO: ejectar el built-in */
		built_ins();
	}
}

int	ejecuter(t_msh *msh)
{
	/* Miramos el numero de comandos que hay que ejecutar */
	if (msh->cmds_count == 1)
	{
		/* Solo ejecutamos un comando */

	}
	else
	{
		/* Ejecutamos varios comandos */
	}
}