#include "../inc/minishell.h"

# define ERROR_MSG "Bad use: ./minishell"
# define MALLOC_MSG "Malloc error"

int	print_error(char *msg)
{
	printf("UwU: %s\n", msg);
	return (1);
}

void leaks()
{
	system("leaks -q minishell");
}

int	main(int argc, char *argv[], char *envp[])
{
	(void) argv;
	t_msh	*data;

	/* atexit(leaks); */

	/* Test de argumentos: no se requiere ninguno */
	if (argc != 1)
		return (print_error(ERROR_MSG));

	/* Inicializar la estructura */
	data = init_msh(envp);
	if (!data)
		return (print_error(MALLOC_MSG));

	/*	TODO: bucle de comandos
			1. Parseo
				-> Mirar comillas
				-> Coge cmd (comando con flags)
				-> Guarda los infiles
				-> Guarda los outfiles
				-> Miramos pipes
			2. Paso intermedio
				-> Nos quitamos los infiles/outfiles useless
				-> Almacenamos ordenadamente la info
			3. Ejecutor
				-> Si es buid-in, ejecuamos su funcion
				-> Sino, pipex
			4. Free memory
				-> xd
	*/

	/* Liberar toda la memoria */
	free_msh(data);

	return (0);
}