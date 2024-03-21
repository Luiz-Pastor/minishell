/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:38:06 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:38:07 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_flag(char *argument)
{
	int	i;

	i = 0;
	if (argument[i] && argument[i] == '-')
		i++;
	else
		return (0);
	if (argument[i] != 'n')
		return (0);
	while (argument[i] != '\0')
	{
		if (argument[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echo_flag_n(char **arguments, int i)
{
	if (!arguments[i])
		return ;
	else
	{
		while (arguments[i])
		{
			printf("%s", arguments[i]);
			if (arguments[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
}

static void	echo_no_flag(char **arguments, int i)
{
	while (arguments[i])
	{
		printf("%s", arguments[i]);
		if (arguments[i + 1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
}

void	bd_echo(t_msh *msh, int nb_comand)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	if (msh->cmds[nb_comand].arguments == NULL)
	{
		printf("\n");
		return ;
	}
	else if (msh->cmds[nb_comand].arguments != NULL)
	{
		while (msh->cmds[nb_comand].arguments[i]
			&& check_flag(msh->cmds[nb_comand].arguments[i]) == 1)
		{
			flag = 1;
			i++;
		}
		if (flag == 1)
			echo_flag_n(msh->cmds[nb_comand].arguments, i);
		else
			echo_no_flag(msh->cmds[nb_comand].arguments, i);
	}
	msh->last_out = 0;
	return ;
}
