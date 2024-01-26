#include "../inc/minishell.h"
#include <string.h>


void	manage(t_msh *data)
{
	int		end;

	end = 0;
	while (1)
	{
		/* TODO: Leemos comandos y añadirlos al historial */
		data->input = readline("minishell> ");
		add_history(data->input);
		/* TODO: parseo */

		/* TODO: Mirar comillas y pedir mas data si hace falta */
		/* TODO: Expandir variables */
		data->input = expand(data);
		if (!data->input)
			return ; // malloc error
		printf("resultado final => [%s]\n", data->input); /* Si se quita no compila porque no se usa en ningun otro lugar */
		/* TODO: paso intermedio */

		/* TODO: ejecutor */

		/* TODO: liberamos memoria */
		if (!strcmp("exit", data->input))
			end = 1;
		if (data->input)
			free(data->input);
		if (end)
			break ;
	}
}