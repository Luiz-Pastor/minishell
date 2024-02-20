#include "../../inc/minishell.h"

static char	**order_alf_envp2(char **new_envp)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (new_envp[i])
	{
		j = i + 1;
		while (new_envp[j])
		{
			if (ft_strcmp(new_envp[i], new_envp[j]) > 0)
			{
				aux = new_envp[i];
				new_envp[i] = new_envp[j];
				new_envp[j] = aux;
			}
			j++;
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static char	**order_alf_envp(char **envp)
{
	char	**new_envp;
	int		lines;
	int		i;

	i = -1;
	lines = 0;
	while (envp[++i])
		lines++;
	new_envp = malloc(sizeof(char *) * (lines + 1));
	if (!new_envp)
		exit_malloc();
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = NULL;
	new_envp = order_alf_envp2(new_envp);
	return (new_envp);
}

void	export_alone(t_msh *msh)
{
	int		i;
	int		j;
	char	**order_envp;

	i = -1;
	order_envp = order_alf_envp(msh->envp);
	if (!order_envp)
		exit_malloc();
	while (order_envp[++i])
	{
		j = 0;
		printf("declare -x ");
		while (order_envp[i][j] != '=' && order_envp[i][j] != '\0')
		{
			printf("%c", order_envp[i][j]);
			j++;
		}
		printf("%c\"", order_envp[i][j++]);
		while (order_envp[i][j] != '\0')
		{
			printf("%c", order_envp[i][j]);
			j++;
		}
		printf("\"\n");
	}
}
