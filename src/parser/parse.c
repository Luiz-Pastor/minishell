#include "../../inc/minishell.h"

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

void	*analize_input(t_msh *msh, int index)
{
	int		i;
	t_cmd	*cmd;

	cmd = &msh->cmds[index];
	i = 0;
	while (cmd->input[i])
	{
		if (cmd->input[i][0] == '<')
			check_infile(1, &i, cmd, msh);
		else if (cmd->input[i][0] == '>')
			check_outfile(1, &i, cmd, msh);
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
static char	**join_cmd_args(char *cmds, char **arguments)
{
	int		i;
	char	**res;
	int		j;

	i = 0;
	while (arguments && arguments[i])
		i++;
	res = malloc(sizeof(char *) * (i + 2));
	if (!res)
		exit_malloc();
	i = 0;
	res[0] = cmds;
	j = 1;
	while (arguments && arguments[i])
	{
		res[j] = arguments[i];
		i++;
		j++;
	}
	res[j] = NULL;
	return (res);
}

void	merge_cmds(t_msh *msh)
{
	int	i;

	i = 0;
	while (i < msh->cmds_count)
	{
		msh->cmds[i].complete_cmd = join_cmd_args(msh->cmds[i].main,
				msh->cmds[i].arguments);
		if (!msh->cmds[i].complete_cmd)
			exit_malloc();
		i++;
	}
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
	merge_cmds(msh);
	return (msh);
}
