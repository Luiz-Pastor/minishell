#include "../../inc/minishell.h"

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

char	*get_part(char *input, int *index)
{
	char	in_quot;
	char	*new;

	in_quot = 0;
	new = NULL;
	while (input[*index])
	{
		if (input[*index] == ' ' && !in_quot)
			break ;
		if (!is_quot(input, *index))
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

	(void)limit;
	index = 0;
	res = NULL;
	while (input[index])
	{
		while (is_space(input[index]))
			index++;
		new = get_part(input, &index);
		// if (!new)
		// 	exit_malloc();
		res = add_part(new, res);
		if (!res)
			return (free_parts(new, NULL));
		if (input[index])
			index++;
	}
	return (res);
}
