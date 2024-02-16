#include "../inc/minishell.h"
#include <string.h>

#define MINISHELL_MSG C_GREENFOSFI"minishell> "CLEAR

void	print_data(t_msh *data)
{
	printf("\nNumero de comandos: %d\n", data->cmds_count);
	int index = 0;
	while (index < data->cmds_count)
	{
		int j;
		printf("--> MAIN: [%s]\n", data->cmds[index].main);
		
		j = 0;
		printf("\tArguments:\n");
		while (data->cmds[index].arguments && data->cmds[index].arguments[j])
			printf("\t\t· [%s]\n", data->cmds[index].arguments[j++]);
		
		j = 0;
		printf("\tInfiles (%d):\n", data->cmds[index].infiles_count);
		while (j < data->cmds[index].infiles_count)
		{
			printf("\t\t-> {[%s], %d}\n", data->cmds[index].infiles[j].name, data->cmds[index].infiles[j].type);
			j++;
		}
		j = 0;
		printf("\tOutfiles (%d):\n", data->cmds[index].outfiles_count);
		while (j < data->cmds[index].outfiles_count)
		{
			printf("\t\t-> {[%s], %d}\n", data->cmds[index].outfiles[j].name, data->cmds[index].outfiles[j].type);
			j++;
		}
		printf("\n==============================================\n\n");
		index++;
	}
}

void	free_cmds(t_msh *data)
{
	int	index;
	int	j;
	/* printf("Liberando memoria\n"); */
	index = -1;
	while (++index < data->cmds_count)
	{
		/* Liberar el input, el nombre del comando y los argumentos del comando */
		free_parts(data->cmds[index].main, data->cmds[index].input);
		free_parts(NULL, data->cmds[index].arguments);

		/* Eliminamos los nombres de los infiles */
		j = -1;
		while (++j < data->cmds[index].infiles_count)
			free(data->cmds[index].infiles[j].name);
		
		/* Eliminamos los nombres de los outfiles */
		j = -1;
		while (++j < data->cmds[index].outfiles_count)
			free(data->cmds[index].outfiles[j].name);

		/* Liberar las array de los io_files */
		ft_mfree(2, &data->cmds[index].infiles, &data->cmds[index].outfiles);
	}
	ft_mfree(2, &data->input, &data->cmds);
}

int	manage(t_msh *data)
{
	int		end;

	end = 0;
	while (1)
	{
		// signals_manage(data);
		/* TODO: Leemos comandos y añadirlos al historial */
		data->input = readline("minishell> ");
		if (!data->input)
		{
			/* TODO: Esto es el ctr+d */
			printf("\n");
			continue ;
		}
		// if (is_empty(data->input)) /*TODO: uwu*/
		// 	continue ;

		/* Mirar comillas y pedir mas data si hace falta */
		data->input = check_quots(data);
		if (!data->input)
		{
			check_error(data);
			continue ;
		}

		/* Guardamos en el historial el comando que se ha intentado ejecutar */
		add_history(data->input);

		/* Parseo */
		if (!parse(data))
		{
			/* TODO: liberar toda la memoria reservada */
			check_error(data);
			continue ;
		}


		/* Imprimimos el texto del input correcto (con las comillas bien) y las variables expandidas */
		printf("========================\n\nFull: {%s}\n\n========================\n", data->input);

		/* TODO: ejecutor */
		executor(data);

		/* TODO: liberamos memoria */
		print_data(data);
		free_cmds(data);
		
		/********************************** Temporal para poder salir de la terminal bien **********************************/
		if (data->input && !strcmp("exit", data->input))
			end = 1;

		/* TODO: liberamos memoria */
		free_cmds(data);

		if (end)
			break ;
	}
	return (0);
}