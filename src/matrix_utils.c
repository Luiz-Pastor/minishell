#include "../inc/minishell.h"

char	**add_part(char *str, char **mtx)
{
	char	**res;
	int		index;


	index = 0;
	while (mtx && mtx[index])
		index++;
	res = ft_calloc(index + 2, sizeof(char **));
	if (!res)
		free_parts(NULL, mtx);
	index = 0;
	while (mtx && mtx[index])
	{
		res[index] = mtx[index];
		index++;
	}
	res[index] = str;
	free(mtx);
	return (res);
}

void	*free_parts(char *part, char **args)
{
	int	index;

	index = 0;
	if (part)
		free(part);
	if (args)
	{
		while (args[index])
			free(args[index++]);
		free(args);
	}
	return (NULL);
}