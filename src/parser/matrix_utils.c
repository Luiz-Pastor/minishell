/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:38 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:39 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**add_part(char *str, char **mtx)
{
	char	**res;
	int		index;

	index = 0;
	while (mtx && mtx[index])
		index++;
	res = ft_calloc(index + 2, sizeof(char **));
	if (!res)
		exit_malloc();
	index = 0;
	while (mtx && mtx[index])
	{
		res[index] = mtx[index];
		index++;
	}
	res[index] = str;
	free(mtx);
	return (res);
}

void	*free_parts(char *part, char **args)
{
	int	index;

	index = 0;
	if (part)
		free(part);
	if (args)
	{
		while (args[index])
			free(args[index++]);
		free(args);
	}
	return (NULL);
}

int	matrix_length(char **mtx)
{
	int	i;

	i = 0;
	while (mtx && mtx[i])
		i++;
	return (i);
}
