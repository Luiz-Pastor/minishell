/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:23 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:24 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
		check_infile(i + 1, index, cmd, msh);
	else if (input[i] == '>')
		check_outfile(i + 1, index, cmd, msh);
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
		check_infile(i + 1, index, cmd, msh);
	else if (input[i] == '>')
		check_outfile(i + 1, index, cmd, msh);
	return (msh);
}
