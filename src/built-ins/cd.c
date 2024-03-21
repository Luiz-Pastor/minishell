/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:38:05 by abarrio-          #+#    #+#             */
/*   Updated: 2024/03/21 12:38:06 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	error_cd(t_msh *msh, char *old, char *new, char *msg)
{
	msh->last_out = 1;
	ft_mfree(2, &old, &new);
	if (!msg)
		perror("uwu: cd");
	else
		printf("%s\n", msg);
}

static char	*get_prev(t_msh *msh)
{
	int		index;
	char	*target;

	index = search_envp(msh->envp, "OLDPWD");
	if (index == -1)
	{
		error_cd(msh, NULL, NULL, "uwu: cd: OLDPWD not set");
		return (NULL);
	}
	target = ft_strdup(&msh->envp[index][7]);
	if (!target)
		exit_malloc();
	printf("%s\n", target);
	return (target);
}

static char	*get_target(t_msh *msh, t_cmd *cmd)
{
	int		index;
	char	*res;

	if (matrix_length(cmd->arguments) && ft_strcmp(cmd->arguments[0], "~"))
	{
		if (!ft_strcmp(cmd->arguments[0], "-"))
			return (get_prev(msh));
		res = ft_strdup(cmd->arguments[0]);
		if (!res)
			exit_malloc();
		return (res);
	}
	index = search_envp(msh->envp, "HOME");
	if (index < 0)
	{
		error_cd(msh, NULL, NULL, "uwu: cd: HOME not set");
		return (NULL);
	}
	res = ft_strdup(&msh->envp[index][5]);
	if (!res)
		exit_malloc();
	return (res);
}

static void	update_env(t_msh *msh, char *old, char *new)
{
	int		index;
	char	*new_pwd;

	index = search_envp(msh->envp, "PWD");
	if (index >= 0)
	{
		new_pwd = ft_strjoin("PWD=", new);
		if (!new_pwd)
			exit_malloc();
		free(msh->envp[index]);
		msh->envp[index] = new_pwd;
	}
	index = search_envp(msh->envp, "OLDPWD");
	if (index == -1)
	{
		msh->envp = insert_envp(msh->envp, ft_strjoin("OLDPWD=", old));
		if (!msh->envp)
			exit_malloc();
	}
	else
		change_envp(msh->envp, "OLDPWD", old);
}

void	bd_cd(t_msh *msh, int nb_comand)
{
	char	*target;
	char	*old_path;
	char	*new_path;
	t_cmd	*current;

	current = &msh->cmds[nb_comand];
	if (current->arguments && !current->arguments[0])
	{
		msh->last_out = 0;
		return ;
	}
	target = get_target(msh, current);
	if (!target)
		return ;
	old_path = getcwd(NULL, 0);
	if (chdir(target) < 0)
		return (error_cd(msh, old_path, target, NULL));
	msh->last_out = 0;
	new_path = getcwd(NULL, 0);
	if (ft_strcmp(old_path, new_path))
		update_env(msh, old_path, new_path);
	ft_mfree(3, &old_path, &new_path, &target);
	return ;
}
