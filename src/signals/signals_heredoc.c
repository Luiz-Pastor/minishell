/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:12 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:13 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ctrl_c_here(int sig)
{
	(void)sig;
	exit(1);
}

void	signals_here_doc(void)
{
	signal(SIGINT, ctrl_c_here);
}
