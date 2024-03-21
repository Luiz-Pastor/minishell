/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:38:17 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:38:18 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*free_expand(char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (NULL);
}

int	ft_correct_var_char(char c, int flag)
{
	if (c == '\\')
		return (1);
	else if (c == '_')
		return (1);
	else if (ft_isalpha(c) == 1)
		return (1);
	else if (flag == MID_LETTER && ft_isdigit(c) == 1)
		return (1);
	return (0);
}
