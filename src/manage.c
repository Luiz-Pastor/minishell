#include "../inc/minishell.h"
#include <string.h>


void	manage(t_msh *data)
{
	(void)data;
	char	*input;

	while (1)
	{
		/* TODO: Leemos comandos y añadirlos al historial */
		input = readline("minishell> ");
		printf("=> [%s]\n", input); /* Si se quita no compila porque no se usa en ningun otro lugar */

		/* TODO: parseo */

		/* TODO: paso intermedio */

		/* TODO: ejecutor */

		/* TODO: liberamos memoria */

	}
}