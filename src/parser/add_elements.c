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

char	**add_command(int start, int end, t_msh *msh, char **res)
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
