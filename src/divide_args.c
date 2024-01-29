#include "../inc/minishell.h"

static char	*get_part(char *str, int *i, char del, int limit)
{
	int		start;
	int		add[2];

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
	add[0] = 0;
	add[1] = 0;
	if (del == '\'' || del == '\"')
	{
		add[0] = limit;
		add[1] =  (-2 * limit) + 1;
	}
	return (ft_substr(str, start + add[0], *i - start + add[1]));
}

char	**divide_cmd_args(char *input, int limit)
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
			new = get_part(input, &index, input[index], limit);
		else
			new = get_part(input, &index, ' ', limit);
		if (!new)
			return (free_parts(new, res));
		res = add_part(new, res);
		if (!res)
			return (free_parts(new, NULL));
		if (input[index])
			index++;
	}
	return (res);
}
