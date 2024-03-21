/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_io_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:22 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:23 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_filename(int start, int *i, char **input)
{
	char	*name;

	if (input[*i][start])
	{
		if (input[*i][start] == '>' || input[*i][start] == '<')
			return (NULL);
		if (input[*i][start] == '\"' || input[*i][start] == '\'')
			name = ft_substr(input[*i], start + 1, \
					ft_strlen(input[*i]) - start - 2);
		else
			name = ft_substr(input[*i], start, ft_strlen(input[*i]) - 1);
	}
	else
	{
		(*i)++;
		if (input[*i][0] == '>' || input[*i][0] == '<')
			return (NULL);
		if (input[*i][0] == '\"' || input[*i][0] == '\'')
			name = ft_substr(input[*i], 1, ft_strlen(input[*i]) - 2);
		else
			name = ft_substr(input[*i], 0, ft_strlen(input[*i]));
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
		msh->here_doc_flag = 2;
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
	if (!input[*index][start] && !input[*index + 1])
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
