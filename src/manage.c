#include "../inc/minishell.h"
#include <string.h>

#define MINISHELL_MSG C_GREENFOSFI"minishell> "CLEAR

int	manage(t_msh *data)
{
	(void)data;
	char	*input;
	int		end;

	end = 0;
	while (1)
	{
		/* TODO: Leemos comandos y añadirlos al historial */
		input = readline("minishell> ");
		if (!input)
		{
			printf("\n");
			continue ;
		}

		/* TODO: parseo */

		/* Mirar comillas y pedir mas data si hace falta */
		input = check_quots(input);
		if (!input)
		{
			printf(C_RED"\nmsh: syntax error: unexpected end of file\n"CLEAR);
			continue ;
		}

		/* Guardamos en el historial el comando que se ha intentado ejecutar */
		add_history(input);

		/* TODO: Expandir variables */

		/* Imprimimos el texto del input correcto (con las comillas bien) y las variables expandidas */
		printf("\t=> [%s]\n", input);

		/* TODO: paso intermedio */

		/* TODO: ejecutor */

		/* TODO: liberamos memoria */
		if (input && !strcmp("exit", input))
			end = 1;
		if (input)
			free(input);

		if (end)
			break ;
	}
	return (0);
}