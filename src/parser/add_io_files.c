#include "../../inc/minishell.h"

void	*add_infile(t_file_type type, char *name, t_cmd *cmd, t_msh *msh)
{
	(void)msh;
	int			index;
	t_io_file	*new;

	new = ft_calloc(cmd->infiles_count + 1, sizeof(t_io_file));
	if (!new)
	{
		/* TODO: malloc error */
		return (NULL);
	}

	/* Copiamos toda la info que teniamos a la nueva estructura */
	index = 0;
	while (index < cmd->infiles_count)
	{
		new[index].name = cmd->infiles[index].name;
		new[index].type = cmd->infiles[index].type;
		index++;
	}
	new[index].name = name;
	new[index].type = type;
	cmd->infiles_count++;

	/* Eliminamos la anterior lista y la actualizamos por la nueva */
	free(cmd->infiles);
	cmd->infiles = new;
	return (msh);
}

void	*add_outfile(t_file_type type, char *name, t_cmd *cmd, t_msh *msh)
{
	(void)msh;
	int			index;
	t_io_file	*new;

	new = ft_calloc(cmd->outfiles_count + 1, sizeof(t_io_file));
	if (!new)
	{
		/* TODO: malloc error */
		return (NULL);
	}

	/* Copiamos toda la info que teniamos a la nueva estructura */
	index = 0;
	while (index < cmd->outfiles_count)
	{
		new[index].name = cmd->outfiles[index].name;
		new[index].type = cmd->outfiles[index].type;
		index++;
	}
	new[index].name = name;
	new[index].type = type;
	cmd->outfiles_count++;

	/* Eliminamos la anterior lista y la actualizamos por la nueva */
	free(cmd->outfiles);
	cmd->outfiles = new;

	return (msh);
}


/*
	> Iterar mientras haya texto
	> Si encuentra " o ', copiar todo lo de dentro, sea lo que sea
	> Si encuentra un '<' o un '>', parar, ejecutar funcion del in/outfile
*/
void	*check_command(int *index, t_cmd *cmd, t_msh *msh)
{
	char	*new;
	char	*input;
	int		i;
	int		in_qt;

	input = cmd->input[*index];
	i = 0;
	in_qt = 0;
	new = NULL;
	while (input[i])
	{
		if (!in_qt && (input[i] == '<' || input[i] == '>'))
			break ;
		if (is_quot(input, i))
			in_qt = !in_qt;
		if ((in_qt && !is_quot(input, i)) || (!in_qt && !is_quot(input, i)))
			new = string_add(new, input[i]);
		i++;
	}

	/* Adjuntamos el comando */
	cmd->main = new;

	/* Miramos si hay una redireccion */
	if (input[i] == '<')
		check_infile(i + 1, index, cmd->input, cmd, msh);
	else if (input[i] == '>')
		check_infile(i + 1, index, cmd->input, cmd, msh);
	return (msh);
}

void	*check_argument(int *index, t_cmd* cmd, t_msh *msh)
{
	char	*new;
	char	*input;
	int		i;
	int		in_qt;

	input = cmd->input[*index];
	i = 0;
	in_qt = 0;
	new = NULL;
	while (input[i])
	{
		if (!in_qt && (input[i] == '<' || input[i] == '>'))
			break ;
		if (is_quot(input, i))
			in_qt = !in_qt;
		if ((in_qt && !is_quot(input, i)) || (!in_qt && !is_quot(input, i)))
			new = string_add(new, input[i]);
		i++;
	}

	/* Añadimos el elemento a la array de argumentos */
	cmd->arguments = add_part(new, cmd->arguments);
	if (!cmd->arguments)
	{
		/* TODO: malloc error */
		return (NULL);
	}
	
	/* Miramos si hay una redireccion */
	if (input[i] == '<')
		check_infile(i + 1, index, cmd->input, cmd, msh);
	else if (input[i] == '>')
		check_infile(i + 1, index, cmd->input, cmd, msh);

	return (msh);
}
