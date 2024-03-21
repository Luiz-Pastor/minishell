/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:25 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:26 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*add_ch(char *str, char ch)
{
	char	*new;
	int		index;

	index = 0;
	new = malloc(ft_strlen(str) + 2);
	if (!new)
		exit_malloc();
	while (str && str[index])
	{
		new[index] = str[index];
		index++;
	}
	new[index] = ch;
	new[index + 1] = '\0';
	if (str)
		free(str);
	return (new);
}

char	*get_part(char *input, int *index)
{
	char	in_quot;
	char	*new;

	in_quot = 0;
	new = NULL;
	while (input[*index])
	{
		if (input[*index] == ' ' && !in_quot)
			break ;
		new = add_ch(new, input[*index]);
		if (is_quot(input, *index) && !in_quot)
			in_quot = input[*index];
		else if (is_quot(input, *index) && in_quot == input[*index])
			in_quot = 0;
		(*index)++;
	}
	return (new);
}

char	**divide_cmd_args(char *input, int limit)
{
	int		index;
	char	*new;
	char	**res;

	(void)limit;
	index = 0;
	res = NULL;
	while (input[index])
	{
		while (is_space(input[index]))
			index++;
		new = get_part(input, &index);
		res = add_part(new, res);
		if (input[index])
			index++;
	}
	return (res);
}
