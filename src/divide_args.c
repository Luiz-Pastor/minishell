#include "../inc/minishell.h"

static int	is_space(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t')
		return (1);
	if (ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

static char	*get_part(char *str, int *i, char del)
{
	char	*new;
	int		start;
	int		add;

	start = (*i);
	(*i)++;
	while (str[(*i)])
	{
		if (del == '\"' && str[*i] == '\"' && str[*i - 1] == '\\')
		{
			(*i)++;
			continue ;
		}
		if (str[*i] == del)
			break ;
		(*i)++;
	}
	add = 0;
	if (del == '\'' || del == '\"')
		add = 1;
	new = ft_substr(str, start + add, *i - start - add);
	return (new);
}

static char	**add_part(char *str, char **mtx)
{
	char	**res;
	int		index;


	index = 0;
	while (mtx && mtx[index])
		index++;
	res = ft_calloc(index + 2, sizeof(char **));
	if (!res)
		return (NULL);
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

static void	*free_parts(char *part, char **args)
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

char	**divide_command(char *input)
{
	int	index;
	char	*new;
	char	**res;

	index = 0;
	res = NULL;
	while (input[index])
	{
		while (is_space(input[index]))
			index++;
		if (input [index] == '\'' || (input[index] == '\"' && (!index || input[index - 1] != '\\')))
			new = get_part(input, &index, input[index]);
		else
			new = get_part(input, &index, ' ');
		if (!new)
			return (free_parts(new, res));
		res = add_part(new, res);
		if (!res)
			return (free_parts(new, res));
		index++;
	}
	return (res);
}
