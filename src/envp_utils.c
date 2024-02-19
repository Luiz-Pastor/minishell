#include "../inc/minishell.h"

int search_envp(char **envp, char *var)
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
	int	length;
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