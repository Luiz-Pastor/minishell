#include "../inc/minishell.h"

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

void	*check_command(char *input, t_cmd *cmd, t_msh *msh)
{
	char	*new;
	(void)msh;

	/* Si empieza y termina por comillas, se las quitamos */
	if (input[0] == '\"' || input[0] == '\'')
		new = ft_substr(input, 1, ft_strlen(input) - 2);
	else
		new = ft_substr(input, 0, ft_strlen(input));
	
	if (!new)
	{
		/* TODO: test de errores */
		return (NULL);
	}

	/* Adjuntamos el comando */
	cmd->main = new;
	printf("\t=> Comando principal: [%s]\n", cmd->main);
	return (msh);
}

void	*check_argument(char *input, t_cmd* cmd, t_msh *msh)
{
	(void)msh;
	char	*new;
	
	/* Si emieza y termina por cmillas se las quitamos */
	if (input[0] == '\"' || input[0] == '\'')
		new = ft_substr(input, 1, ft_strlen(input) - 2);
	else
		new = ft_substr(input, 0, ft_strlen(input));

	/* Añadimos el elemento a la array de argumentos */
	cmd->arguments = add_part(new, cmd->arguments);
	if (!cmd->arguments)
	{
		/* TODO: malloc error */
		return (NULL);
	}
	printf("\t=> Argumento del programa: [%s]\n", new);
	return (msh);
}