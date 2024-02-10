#include "../../inc/minishell.h"

/* UN COMANDO

Primero mirar si es built-in o no:
	- Si es un comando:
		- Crear un proceso hijo
		- Abrir todos los infiles y nos quedamos con el ultmo (o con stdin si no hay ninguno)
		- Abrimos todos los outfiles y nos quedasmo con el ultimo (o con stdout si no hay ninguno)
		- Sacar la ruta del comando
		- Juntar comando con argumentos
		- Hacer los dups
		- Hacer execve

Cosas a mirar en los build-ins
	- Abrir todos los infiles y nos quedamos con el ultmo (o con stdin si no hay ninguno)
	- Abrimos todos los outfiles y nos quedasmo con el ultimo (o con stdout si no hay ninguno)
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

/* VARIOS COMANDOS

Desde el padre, creamos tanto forks como comands haya.
Para cada uno de los comandos:
	- Abrir todos los infiles y nos quedamos con el ultmo (o con stdin si no hay ninguno)
	- Abrimos todos los outfiles y nos quedasmo con el ultimo (o con stdout si no hay ninguno)
	- Sacar la ruta del comando
	- Juntar comando con argumentos
	- Hacer los dups
	- Hacer execve

*/

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