/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:38:14 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:38:15 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	*bd_pwd(t_msh *msh)
{
	char	*path;

	msh->last_out = 0;
	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
	return (NULL);
}
