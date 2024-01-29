#include "../inc/minishell.h"

int	is_quot(char *input, int index)
{
	/* Miramos si es una comilla */
	if (input[index] != '\'' && input[index] != '\"')
		return (0);
	
	/* Si es simple, es o inicio o fin (no tiene escape posible) */
	if (input[index] == '\'')
		return (1);

	/* Aqui es doble seguro, miramos si es el primer caracter o si tiene escape*/
	return (input == 0 || input[index - 1] != '\\');
}