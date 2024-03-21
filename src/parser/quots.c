/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quots.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:42 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:43 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// #define	QUOTE_MSG C_CYAN"dquote> "CLEAR

static char	*dquote(t_msh *msh)
{
	char	*new_line;
	char	*inter;
	char	*full;

	new_line = readline("dquote> ");
	if (!new_line)
	{
		ft_mfree(1, &msh->input);
		return (set_error(CTR_D, msh));
	}
	inter = ft_strjoin(msh->input, "\n");
	if (!inter)
		exit_malloc();
	full = ft_strjoin(inter, new_line);
	if (!full)
		exit_malloc();
	ft_mfree(3, &msh->input, &inter, &new_line);
	return (full);
}

static int	next_quot(char *input, int i)
{
	char	ch;

	ch = input[i];
	while (input[++i])
	{
		if (input[i] == ch && is_quot(input, i))
			return (i);
	}
	return (-1);
}

char	*check_quots(t_msh *msh)
{
	int	i;
	int	next;

	i = 0;
	while (msh->input[i])
	{
		if (is_quot(msh->input, i))
		{
			next = next_quot(msh->input, i);
			if (next == -1)
			{
				msh->input = dquote(msh);
				if (!msh->input)
					return (NULL);
				i--;
			}
			else
				i = next;
		}
		i++;
	}
	return (msh->input);
}
