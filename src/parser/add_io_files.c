#include "../../inc/minishell.h"

void	*add_infile(t_file_type type, char *name, t_cmd *cmd)
{
	int			index;
	t_io_file	*new;

	index = 0;
	new = ft_calloc(cmd->infiles_count + 1, sizeof(t_io_file));
	if (!new)
		exit_malloc();
	while (index < cmd->infiles_count)
	{
		new[index].name = cmd->infiles[index].name;
		new[index].type = cmd->infiles[index].type;
		index++;
	}
	new[index].name = name;
	new[index].type = type;
	cmd->infiles_count++;
	free(cmd->infiles);
	cmd->infiles = new;
	return (cmd);
}

void	*add_outfile(t_file_type type, char *name, t_cmd *cmd)
{
	int			index;
	t_io_file	*new;

	index = 0;
	new = ft_calloc(cmd->outfiles_count + 1, sizeof(t_io_file));
	if (!new)
		exit_malloc();
	while (index < cmd->outfiles_count)
	{
		new[index].name = cmd->outfiles[index].name;
		new[index].type = cmd->outfiles[index].type;
		index++;
	}
	new[index].name = name;
	new[index].type = type;
	cmd->outfiles_count++;
	free(cmd->outfiles);
	cmd->outfiles = new;
	return (cmd);
}

char	*sub_arguments(char *input, int *i)
{
	char	in_qt;
	char	*new;

	new = NULL;
	in_qt = 0;
	while (input[*i])
	{
		if (!in_qt && (input[*i] == '<' || input[*i] == '>'))
			break ;
		if (!in_qt && is_quot(input, *i))
			in_qt = input[*i];
		else if (in_qt == input[*i] && is_quot(input, *i))
			in_qt = !in_qt;
		if ((in_qt && (!is_quot(input, *i) || input[*i] != in_qt)) || \
			(!in_qt && !is_quot(input, *i)))
			new = string_add(new, input[*i]);
		(*i)++;
	}
	return (new);
}

void	*check_command(int *index, t_cmd *cmd, t_msh *msh)
{
	char	*input;
	int		i;

	i = 0;
	input = cmd->input[*index];
	cmd->main = sub_arguments(input, &i);
	if (input[i] == '<')
		check_infile(i + 1, index, cmd->input, cmd, msh);
	else if (input[i] == '>')
		check_outfile(i + 1, index, cmd->input, cmd, msh);
	return (msh);
}

void	*check_argument(int *index, t_cmd *cmd, t_msh *msh)
{
	char	*input;
	int		i;

	i = 0;
	input = cmd->input[*index];
	cmd->arguments = add_part(sub_arguments(input, &i), cmd->arguments);
	if (!cmd->arguments)
		exit_malloc();
	if (input[i] == '<')
		check_infile(i + 1, index, cmd->input, cmd, msh);
	else if (input[i] == '>')
		check_outfile(i + 1, index, cmd->input, cmd, msh);
	return (msh);
}
