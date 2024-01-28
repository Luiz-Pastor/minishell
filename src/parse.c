#include "../inc/minishell.h"

static char	**add_command(int start, int end, char *input, char **res)
{
	char	*cmd;
	
	/* Ajustamos el start y en end para quitar los espacios */
	while (input[start] && is_space(input[start]))
		start++;
	while (end >= 0 && input[end] && is_space(input[end]))
		end--;
	
	/* TODO: mirar que al quitar espacios haya un problema de sintaxis (ej: | ls)*/
	if (end < start)
	{
		/* Error: mala sintaxis */
		printf("Mala sintaxis.\n");
		free_parts(NULL, res);
		return (NULL);
	}

	/* Sabiendo el inicio y el final correctos, sacamos este texto */
	cmd = ft_substr(input, start, end - start + 1);
	if (!cmd)
		return (free_parts(NULL, res));

	/* Añadimos el elemento a la array de strings */
	res = add_part(cmd, res);
	if (!res)
		return (free_parts(cmd, NULL));
	
	return (res);
}

static char	**split_commands(char *input)
{
	int		index;
	char	quot;
	char	**res;
	int		start;

	index = 0;
	start = 0;
	quot = 0;
	res = NULL;
	while (input[index])
	{
		if (quot && input[index] == quot && is_quot(input, index))
			quot = 0; /* Se cierra el quot */
		else if (!quot && is_quot(input, index))
			quot = input[index]; /* Se abre el quot */

		/* Si encontramos una barra y no esta entre comillas, hemos encaontrado un comando */
		if (input[index] == '|' && !quot)
		{
			/* TODO: Añadir comando */
			res = add_command(start, index - 1, input, res);
			if (!res)
				return (NULL);
			start = index + 1;
		}
		index++;
	}
	return (add_command(start, index - 1, input, res));
}

void	*check_infile(int *index, char **input, t_cmd *cmd, t_msh *msh)
{
	t_file_type	tp;
	char	*name;
	int		i = 1;

	tp = INFILE;
	if (input[*index][1] == '<')
	{
		tp = HERE_DOC;
		i++;
	}

	if (input[*index][i])
	{
		/* TODO: si hay algo en el siguiente caracter despues del <, es el nombre del archivo/del */
		/* Miramos si hay comillas, entonces tendriamos que quitar las del final tambien*/
		if (input[*index][i] == '\"' || input[*index][i] == '\'')
			name = ft_substr(input[*index], i + 1, ft_strlen(input[*index]) - i - 2);
		else
			name = ft_substr(input[*index], i, ft_strlen(input[*index]) - 1);
	}
	else
	{
		/* TODO: el nombre es el siguiente argumento */
		(*index)++;
		/* Miramos si hay comillas, entonces tendriamos que quitar las del final tambien*/

		if (input[*index][0] == '>' || input[*index][0] == '<')
		{
			/* TODO: error */
		}

		if (input[*index][0] == '\"' || input[*index][0] == '\'')
			name = ft_substr(input[*index], 1, ft_strlen(input[*index]) - 2);
		else
			name = ft_substr(input[*index], 0, ft_strlen(input[*index]));
	}
	printf("###> Encontrado infile: {[%s], %d}\n", name, tp);
	add_infile(tp, name, cmd, msh);
	return (msh);
}

void	analize_input(t_msh *msh, int index)
{
	int		i;
	t_cmd	cmd;

	cmd = msh->cmds[index];
	// i = 0;
	// while (cmd.input[i])
	// 	printf("\t-> [%s]\n", cmd.input[i++]);
	// printf("\n\n");

	/* TODO: nos recorremos toda la array con los elementos del comando ([wc] [-l] [NULL])*/
	i = 0;
	while (cmd.input[i])
	{
		if (cmd.input[i][0] == '<')
		{
			/* TODO: Si empieza por '<', es infile o él o la siguiente parte */
			check_infile(&i, cmd.input, &cmd, msh);
		}
		else if (cmd.input[i][0] == '>')
		{
			/* TODO: Si empieza por '>', es outfile o él o la siguiente parte */

		}
		else
		{
			/* TODO: Si no es nada de lo anterior, es o comando o algumento/flag */

		}

		i++;
	}
}

void	*parse(t_msh *msh)
{
	char	**cmds;
	int		index;

	/* TODO: Expandimos las variables ue hacen falta */

	/* TODO: dividir cada parte en los comandos que tengan */
	cmds = split_commands(msh->input);
	if (!cmds)
		return (NULL);

	// int index = -1;
	// while (cmds && cmds[++index])
	// 	printf("=> CMD(%d): [%s]\n", index, cmds[index]);

	/* Sabiendo el numero de comandos, creamos la array, y guardamos la info de cada comando */
	/* Inicializamos la estructura */
	msh->cmds_count = matrix_length(cmds);
	if (!create_commands(msh))
		return (NULL);
	
	/* Para cada comando, miramos sus tokens */
	index = 0;
	while (cmds[index])
	{
		printf("{Mirando: [%s]}\n", cmds[index]);
		msh->cmds[index].input = divide_cmd_args(cmds[index], WITH_QUOT);
		analize_input(msh, index);
		index++;
		printf("\n\n");
	}

	

	return (msh);
}
