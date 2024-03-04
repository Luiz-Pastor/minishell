#include "../../inc/minishell.h"

/*void	set_calc(int *add, int limit, char del)
{
	add[0] = 0;
	add[1] = 0;
	if (del == '\'' || del == '\"')
	{
		add[0] = limit;
		add[1] = (-2 * limit) + 1;
	}
}

char	*get_part(char *str, int *i, char del, int limit)
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
		{
			while (str[*i + 1] && str[*i] != ' ' && str[*i + 1] != ' ')
				(*i)++;
			break ;
		}
		(*i)++;
	}
	set_calc(add, limit, del);
	return (ft_substr(str, start + add[0], *i - start + add[1]));
}*/

char	*add_ch(char *str, char ch)
{
	char	*new;
	int		index;

	index = 0;
	new = malloc(ft_strlen(str) + 2);
	if (!new)
		exit_malloc();
	while (str && str[index])
	{
		new[index] = str[index];
		index++;
	}
	new[index] = ch;
	new[index + 1] = '\0';
	if (str)
		free(str);
	return (new);
}

char *get_part2(char *input, int *index)
{
	char	in_quot;
	int		start;
	char	*new;

	start = *index;
	in_quot = 0;
	new = NULL;
	while (input[*index])
	{
		if (input[*index] == ' ' && !in_quot)
			break ;
		if (!is_quot(input, *index) )
			new = add_ch(new, input[*index]);
		else if (is_quot(input, *index) && in_quot && input[*index] != in_quot)
			new = add_ch(new, input[*index]);
		if (is_quot(input, *index) && !in_quot)
			in_quot = input[*index];
		else if (is_quot(input, *index) && in_quot == input[*index])
			in_quot = 0;
		(*index)++;
	}
	return (new);
}

char	**divide_cmd_args(char *input, int limit)
{
	int		index;
	char	*new;
	char	**res;

	(void) limit;
	index = 0;
	res = NULL;
	while (input[index])
	{
		while (is_space(input[index]))
			index++;
		/*if (input [index] == '\'' || (input[index] == '\"' && (!index || \
			input[index - 1] != '\\')))
			new = get_part(input, &index, input[index], limit);
		else
			new = get_part(input, &index, ' ', limit);*/
		new = get_part2(input, &index);
		if (!new)
			exit_malloc();
		res = add_part(new, res);
		if (!res)
			return (free_parts(new, NULL));
		if (input[index])
			index++;
	}
	return (res);
}
