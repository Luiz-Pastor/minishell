#include "../inc/minishell.h"

static char	**add_command(int start, int end, t_msh *msh, char **res)
{
	char	*cmd;
	
	/* Ajustamos el start y en end para quitar los espacios */
	while (msh->input[start] && is_space(msh->input[start]))
		start++;
	while (end >= 0 && msh->input[end] && is_space(msh->input[end]))
		end--;
	
	/* TODO: mirar que al quitar espacios haya un problema de sintaxis (ej: | ls)*/
	if (end < start)
	{
		/* Error: mala sintaxis */
		set_error(SYNTAX, msh);
		free_parts(NULL, res);
		return (NULL);
	}

	/* Sabiendo el inicio y el final correctos, sacamos este texto */
	cmd = ft_substr(msh->input, start, end - start + 1);
	if (!cmd)
	{
		free_parts(NULL, res);
		return (set_error(MALLOC, msh));
	}

	/* Añadimos el elemento a la array de strings */
	res = add_part(cmd, res);
	if (!res)
	{
		free_parts(cmd, NULL);
		return (set_error(MALLOC, msh));
	}
	return (res);
}

static char	**split_commands(t_msh *msh)
{
	int		index;
	char	quot;
	char	**res;
	int		start;

	index = 0;
	start = 0;
	quot = 0;
	res = NULL;
	while (msh->input[index])
	{
		if (quot && msh->input[index] == quot && is_quot(msh->input, index))
			quot = 0; /* Se cierra el quot */
		else if (!quot && is_quot(msh->input, index))
			quot = msh->input[index]; /* Se abre el quot */

		/* Si encontramos una barra y no esta entre comillas, hemos encaontrado un comando */
		if (msh->input[index] == '|' && !quot)
		{
			/* Añadir comando */
			res = add_command(start, index - 1, msh, res);
			if (!res)
				return (NULL);
			start = index + 1;
		}
		index++;
	}
	return (add_command(start, index - 1, msh, res));
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
		if (input[*index][i] == '\"' || input[*index][i] == '\'')
			name = ft_substr(input[*index], i + 1, ft_strlen(input[*index]) - i - 2);
		else
			name = ft_substr(input[*index], i, ft_strlen(input[*index]) - 1);
	}
	else
	{
		(*index)++;
		if (input[*index][0] == '>' || input[*index][0] == '<')
			return (set_error(SYNTAX, msh));
		if (input[*index][0] == '\"' || input[*index][0] == '\'')
			name = ft_substr(input[*index], 1, ft_strlen(input[*index]) - 2);
		else
			name = ft_substr(input[*index], 0, ft_strlen(input[*index]));
	}
	if (!name || !add_outfile(tp, name, cmd, msh))
	{
		set_error(MALLOC, msh);
		return (NULL);
	}
	printf("\t=> Encontrado infile: {[%s], %d}\n", name, tp);
	return (msh);
}

void	*check_outfile(int *index, char **input, t_cmd *cmd, t_msh *msh)
{
	t_file_type	tp;
	char	*name;
	int		i = 1;

	tp = TRUNC;
	if (input[*index][1] == '>')
	{
		tp = APPEND;
		i++;
	}

	if (input[*index][i])
	{
		if (input[*index][i] == '\"' || input[*index][i] == '\'')
			name = ft_substr(input[*index], i + 1, ft_strlen(input[*index]) - i - 2);
		else
			name = ft_substr(input[*index], i, ft_strlen(input[*index]) - 1);
	}
	else
	{
		(*index)++;
		if (input[*index][0] == '>' || input[*index][0] == '<')
			return (set_error(SYNTAX, msh));
		if (input[*index][0] == '\"' || input[*index][0] == '\'')
			name = ft_substr(input[*index], 1, ft_strlen(input[*index]) - 2);
		else
			name = ft_substr(input[*index], 0, ft_strlen(input[*index]));
	}
	if (!name || !add_outfile(tp, name, cmd, msh))
	{
		set_error(MALLOC, msh);
		return (NULL);
	}
	printf("\t=> Encontrado outfile: {[%s], %d}\n", name, tp);
	return (msh);
}

void	*analize_input(t_msh *msh, int index)
{
	int		i;
	t_cmd	cmd;

	cmd = msh->cmds[index];

	/* Nos recorremos toda la array con los elementos del comando ([wc] [-l] [NULL])*/
	i = 0;
	while (cmd.input[i])
	{
		if (cmd.input[i][0] == '<')
			check_infile(&i, cmd.input, &cmd, msh);
		else if (cmd.input[i][0] == '>')
			check_outfile(&i, cmd.input, &cmd, msh);
		else
		{
			if (!cmd.main)
				check_command(cmd.input[i], &cmd, msh);
			else
				check_argument(cmd.input[i], &cmd, msh);
		}
		if (is_error(msh))
			return (NULL);
		i++;
	}
	return (msh);
}

void	*parse(t_msh *msh)
{
	char	**cmds;
	int		index;

	/* TODO: Expandimos las variables ue hacen falta */

	/* Dividir cada parte en los comandos que tengan */
	cmds = split_commands(msh);
	if (!cmds)
		return (NULL);

	/* Sabiendo el numero de comandos, creamos la array, y guardamos la info de cada comando */
	/* Inicializamos la estructura */
	msh->cmds_count = matrix_length(cmds);
	if (!create_commands(msh))
		return (set_error(MALLOC, msh));
	
	/* Para cada comando, miramos sus tokens */
	index = 0;
	while (cmds[index])
	{
		printf("{Mirando: [%s]}\n", cmds[index]);
		msh->cmds[index].input = divide_cmd_args(cmds[index], WITH_QUOT);
		if (!analize_input(msh, index))
			return (free_parts(NULL, cmds));
		index++;
		printf("\n\n");
	}

	/* Liberar cmds */
	free_parts(NULL, cmds);

	return (msh);
}
