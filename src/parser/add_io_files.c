#include "../../inc/minishell.h"

static char	*get_filename(int start, int *index, char **input)
{
	char	*name;

	if (input[*index][start])
	{
		if (input[*index][start] == '\"' || input[*index][start] == '\'')
			name = ft_substr(input[*index], start + 1, \
					ft_strlen(input[*index]) - start - 2);
		else
			name = ft_substr(input[*index], start, \
					ft_strlen(input[*index]) - 1);
	}
	else
	{
		(*index)++;
		if (input[*index][0] == '>' || input[*index][0] == '<')
			return (NULL);
		if (input[*index][0] == '\"' || input[*index][0] == '\'')
			name = ft_substr(input[*index], 1, ft_strlen(input[*index]) - 2);
		else
			name = ft_substr(input[*index], 0, ft_strlen(input[*index]));
	}
	if (!name)
		exit_malloc();
	return (name);
}

void	*check_infile(int start, int *index, t_cmd *cmd, t_msh *msh)
{
	t_file_type	tp;
	char		*name;
	char		**input;

	input = cmd->input;
	tp = INFILE;
	if (input[*index][start] == '<')
	{
		tp = HERE_DOC;
		start++;
	}
	if (!input[*index][start] && !input[*index + 1])
	{
		set_error(SYNTAX, msh);
		return (msh);
	}
	name = get_filename(start, index, input);
	if (!name)
		return (set_error(SYNTAX, msh));
	if (!add_infile(tp, name, cmd))
		exit_malloc();
	return (msh);
}

void	*check_outfile(int start, int *index, t_cmd *cmd, t_msh *msh)
{
	t_file_type	tp;
	char		*name;
	char		**input;

	input = cmd->input;
	tp = TRUNC;
	if (input[*index][start] == '>')
	{
		tp = APPEND;
		start++;
	}
	if (!input[*index])
	{
		set_error(SYNTAX, msh);
		return (msh);
	}
	name = get_filename(start, index, input);
	if (!name)
		return (set_error(SYNTAX, msh));
	if (!add_outfile(tp, name, cmd))
		exit_malloc();
	return (msh);
}
