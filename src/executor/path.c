#include "../../inc/minishell.h"

static int	is_full_path(t_cmd *cmds)
{
	int	i;

	i = 0;
	while (cmds->main[i])
	{
		if (cmds->main[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

static char	*built_aux(t_cmd *cmds, char **path_list)
{
	char	*path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		path = ft_strdup(path_list[i]);
		if (!path)
			return (NULL);
		path = ft_gnl_strjoin(path, "/");
		if (!path)
			return (NULL);
		path = ft_gnl_strjoin(path, cmds->main);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		i++;
	}
	return (path);
}

static char	*build_path(t_cmd *cmds, char **path_list)
{
	char	*path;

	if (path_list == NULL || is_full_path(cmds) == 1)
	{
		path = ft_strdup(cmds->main);
		if (!path)
			exit_malloc();
	}
	else
		path = built_aux(cmds, path_list);
	return (path);
}

static char	**get_path_list(char **envp)
{
	char	**path_list;
	int		i;

	if (envp[0] == NULL)
		path_list = NULL;
	else
	{
		i = 0;
		while (envp[i] != NULL)
		{
			if (!ft_strncmp(envp[i], "PATH=", 5))
				break ;
			i++;
		}
		if (envp[i] == NULL)
			return (NULL);
		path_list = ft_split(&envp[i][5], ':');
		if (!path_list)
			exit_malloc();
	}
	return (path_list);
}

char	*get_path(t_cmd *cmds, char **envp)
{
	char	**path_list;
	char	*path_cmd;

	(void)envp, (void)cmds;
	path_list = get_path_list(envp);
	path_cmd = build_path(cmds, path_list);
	if (!path_cmd)
		exit_malloc();
	free(path_list);
	return (path_cmd);
}
