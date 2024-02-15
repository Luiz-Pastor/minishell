#include "../../inc/minishell.h"

static char	**add_command(int start, int end, t_msh *msh, char **res)
{
	char	*cmd;

	while (msh->input[start] && is_space(msh->input[start]))
		start++;
	while (end >= 0 && msh->input[end] && is_space(msh->input[end]))
		end--;
	if (end < start)
	{
		set_error(SYNTAX, msh);
		free_parts(NULL, res);
		return (NULL);
	}
	cmd = ft_substr(msh->input, start, end - start + 1);
	if (!cmd)
		exit_malloc();
	res = add_part(cmd, res);
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
			quot = 0;
		else if (!quot && is_quot(msh->input, index))
			quot = msh->input[index];
		if (msh->input[index] == '|' && !quot)
		{
			res = add_command(start, index - 1, msh, res);
			if (!res)
				return (NULL);
			start = index + 1;
		}
		index++;
	}
	return (add_command(start, index - 1, msh, res));
}

void	*check_infile(int start, int *index, char **input, t_cmd *cmd, t_msh *msh)
{
	t_file_type	tp;
	char		*name;

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
	if (input[*index][start])
	{
		if (input[*index][start] == '\"' || input[*index][start] == '\'')
			name = ft_substr(input[*index], start + 1, ft_strlen(input[*index]) - start - 2);
		else
			name = ft_substr(input[*index], start, ft_strlen(input[*index]) - 1);
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
	if (!name || !add_infile(tp, name, cmd))
		exit_malloc();
	return (msh);
}

void	*check_outfile(int start, int *index, char **input, t_cmd *cmd, t_msh *msh)
{
	t_file_type	tp;
	char		*name;

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
	if (input[*index][start])
	{
		if (input[*index][start] == '\"' || input[*index][start] == '\'')
			name = ft_substr(input[*index], start + 1, ft_strlen(input[*index]) - start - 2);
		else
			name = ft_substr(input[*index], start, ft_strlen(input[*index]) - 1);
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
	if (!name || !add_outfile(tp, name, cmd))
		exit_malloc();
	return (msh);
}

void	*analize_input(t_msh *msh, int index)
{
	int		i;
	t_cmd	*cmd;

	cmd = &msh->cmds[index];
	i = 0;
	while (cmd->input[i])
	{
		if (cmd->input[i][0] == '<')
			check_infile(1, &i, cmd->input, cmd, msh);
		else if (cmd->input[i][0] == '>')
			check_outfile(1, &i, cmd->input, cmd, msh);
		else
		{
			if (!cmd->main)
				check_command(&i, cmd, msh);
			else
				check_argument(&i, cmd, msh);
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

	msh->input = expand(msh);
	cmds = split_commands(msh);
	if (!cmds)
		return (NULL);
	msh->cmds_count = matrix_length(cmds);
	if (!create_commands(msh))
		exit_malloc();
	index = 0;
	while (cmds[index])
	{
		msh->cmds[index].input = divide_cmd_args(cmds[index], WITH_QUOT);
		if (!analize_input(msh, index))
			return (free_parts(NULL, cmds));
		index++;
	}
	free_parts(NULL, cmds);
	return (msh);
}
