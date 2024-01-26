#include "../inc/minishell.h"

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
			return (free_parts(new, NULL));
		index++;
	}
	return (res);
}
