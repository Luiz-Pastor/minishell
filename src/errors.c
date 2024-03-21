/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:36:52 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:01 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	*set_error(t_error error, t_msh *msh)
{
	if (msh)
		msh->error = error;
	return (NULL);
}

void	exit_malloc(void)
{
	perror(MALLOC_MSG);
	exit(1);
}

void	exit_fork_pipe(t_error error)
{
	if (error == PIPE)
		perror(ERROR_PIPE_MSG);
	else if (error == FORK)
		perror(ERROR_FORK_MSG);
	exit(1);
}

void	check_error(t_msh *msh, int flag)
{
	t_error	error;

	error = msh->error;
	if (error == SYNTAX)
		ft_putstr_fd("uwu: syntax error near unexpected token\n",
			STDERR_FILENO);
	else if (error == CTR_D)
		ft_putstr_fd("uwu: syntax error: unexpected end of file\n",
			STDERR_FILENO);
	msh->error = NONE;
	if (flag)
		free_cmds(msh);
}

int	is_error(t_msh *msh)
{
	return (msh->error);
}
