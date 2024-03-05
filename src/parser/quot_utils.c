#include "../../inc/minishell.h"

int	is_quot(char *input, int index)
{
	if (input[index] != '\'' && input[index] != '\"')
		return (0);
	if (input[index] == '\'')
		return (1);
	return (index == 0 || input[index - 1] != '\\');
}
