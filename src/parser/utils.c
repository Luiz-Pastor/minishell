/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:43 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:44 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_space(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t')
		return (1);
	if (ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

char	*string_add(char *str, char ch)
{
	int		i;
	char	*new;

	i = 0;
	new = malloc(ft_strlen(str) + 2);
	if (!new)
		exit_malloc();
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	new[i] = ch;
	new[i + 1] = '\0';
	return (new);
}
