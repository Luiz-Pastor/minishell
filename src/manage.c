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
			printf("\n");
			continue ;
		}

		/* Mirar comillas y pedir mas data si hace falta */
		data->input = check_quots(data->input);
		if (!data->input)
		{
			printf(C_RED"\nmsh: syntax error: unexpected end of file\n"CLEAR);
			continue ;
		}

		/* Guardamos en el historial el comando que se ha intentado ejecutar */
		add_history(data->input);

		/* TODO: Expandir variables */

		/* TODO: parseo */
		parse(data);

		/* Imprimimos el texto del input correcto (con las comillas bien) y las variables expandidas */
		printf("\t=> [%s]\n", data->input);

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