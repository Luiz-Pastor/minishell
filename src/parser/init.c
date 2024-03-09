#include "../../inc/minishell.h"

static void	*clean_env(char *envp[], int max)
{
	int	i;

	i = 0;
	if (max < 0)
	{
		while (envp && envp[i])
			free(envp[i++]);
	}
	else
	{
		while (i < max)
			free(envp[i++]);
	}
	free(envp);
	return (NULL);
}

void	*free_msh(t_msh *data)
{
	if (!data)
		return (NULL);
	if (data->envp)
		clean_env(data->envp, -1);
	free(data);
	return (NULL);
}

static char	**small_envp(void)
{
	char	*path;
	char	**new_env;

	new_env = ft_calloc(3, sizeof(char *));
	if (!new_env)
		exit_malloc();
	path = getcwd(NULL, 0);
	new_env[0] = ft_strjoin("PWD=", path);
	free(path);
	if (!new_env[0])
		return (clean_env(new_env, 0));
	new_env[2] = ft_strdup("_=/usr/bin/env");
	if (!new_env[2])
		return (clean_env(new_env, 2));
	return (new_env);
}

static char	**copy_env(char *envp[])
{
	int		i;
	char	**new_env;

	i = 0;
	if (envp[0] == NULL)
		return (small_envp());
	while (envp[i])
		i++;
	new_env = ft_calloc((i + 1), sizeof(char *));
	if (!new_env)
		exit_malloc();
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
			return (clean_env(new_env, i));
		i++;
	}
	return (new_env);
}

t_msh	*init_msh(char *envp[])
{
	t_msh	*data;

	data = malloc (sizeof(t_msh));
	if (!data)
		exit_malloc();
	ft_memset(data, 0, sizeof(t_msh));
	data->cpy_stdin = dup(STDIN_FILENO);
	data->cpy_stdout = dup(STDOUT_FILENO);
	data->envp = mod_envp_shlvl(copy_env(envp));
	if (!data->envp)
		return (free_msh(data));
	return (data);
}
