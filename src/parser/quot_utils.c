/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quot_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:41 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:42 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quot(char *input, int index)
{
	if (input[index] != '\'' && input[index] != '\"')
		return (0);
	if (input[index] == '\'')
		return (1);
	return (index == 0 || input[index - 1] != '\\');
}
