#include "../inc/minishell.h"
#include <string.h>

#define MINISHELL_MSG C_GREENFOSFI"minishell> "CLEAR

int	manage(t_msh *data)
{
	int		end;

	end = 0;
	while (1)
	{
		/* TODO: Leemos comandos y añadirlos al historial */
		data->input = readline("minishell> ");
		if (!data->input)
		{
			/* TODO: Esto es el ctr+d */
			printf("\n");
			continue ;
		}

		/* Mirar comillas y pedir mas data si hace falta */
		data->input = check_quots(data);
		if (!data->input)
		{
			check_error(data);
			continue ;
		}

		/* Guardamos en el historial el comando que se ha intentado ejecutar */
		add_history(data->input);

		/* TODO: Expandir variables */

		/* Parseo */
		if (!parse(data))
		{
			/* TODO: liberar toda la memoria reservada */
			check_error(data);
			continue ;
		}

		/* Imprimimos el texto del input correcto (con las comillas bien) y las variables expandidas */
		printf("========================\n\nFull: {%s}\n\n========================\n", data->input);

		/* TODO: paso intermedio */

		/* TODO: ejecutor */

		/* TODO: liberamos memoria */
		
		/********************************** Temporal para poder salir de la terminal bien **********************************/
		if (data->input && !strcmp("exit", data->input))
			end = 1;
		if (data->input)
			free(data->input);
		if (end)
			break ;
	}
	return (0);
}