/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:37:09 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:37:10 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**mod_envp_shlvl(char **envp)
{
	int		i;
	int		nb;
	char	*aux;
	char	*shlvl;

	i = search_envp(envp, "SHLVL");
	if (i == -1)
	{
		shlvl = ft_strjoin("SHLVL=", "1");
		if (!shlvl)
			exit_malloc();
		return (insert_envp(envp, shlvl));
	}
	nb = ft_atoi(&envp[i][6]);
	free(envp[i]);
	nb += 1;
	aux = ft_itoa(nb);
	if (!aux)
		exit_malloc();
	envp[i] = ft_strjoin("SHLVL=", aux);
	if (!envp[i])
		exit_malloc();
	free(aux);
	return (envp);
}

int	search_envp(char **envp, char *var)
{
	int		index;
	char	*full;

	index = 0;
	full = ft_strjoin(var, "=");
	if (!full)
		exit_malloc();
	while (envp && envp[index])
	{
		if (!ft_strncmp(envp[index], full, ft_strlen(full)))
		{
			free(full);
			return (index);
		}
		index++;
	}
	free(full);
	return (-1);
}

char	**insert_envp(char **envp, char *var)
{
	int		length;
	char	**new_envp;

	length = 0;
	while (envp && envp[length])
		length++;
	new_envp = ft_calloc(length + 2, sizeof(char *));
	if (!new_envp)
		exit_malloc();
	length = -1;
	while (envp && envp[++length])
		new_envp[length] = envp[length];
	new_envp[length] = var;
	return (new_envp);
}

void	change_envp(char **envp, char *search, char *data)
{
	int		index;
	char	*new;
	char	*mid;

	index = search_envp(envp, search);
	if (index < 0)
		return ;
	mid = ft_strjoin(search, "=");
	if (!mid)
		exit_malloc();
	new = ft_strjoin(mid, data);
	if (!new)
		exit_malloc();
	free(mid);
	free(envp[index]);
	envp[index] = new;
}
