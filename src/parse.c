#include "../inc/minishell.h"

char	**add_command(int index, char *input, char **res)
{
	int		start;
	char	*new;

	while (index >= 0 && is_space(input[index]))
		index--;
	start = index;
	while (start >= 0 && start != '|')
		start--;
	new = ft_substr(input, start + 1, index - start);
	if (!new)
		return (free_parts(new, res));
	res = add_part(new, res);
	if (!res)
		return (free_parts(new, NULL));
	return (res);
}

char	**split_commands(char *input)
{
	int		index;
	char	quot;
	char	**res;

	index = 0;
	quot = 0;
	res = NULL;
	while (input[index])
	{
		if (quot && input[index] == quot && is_quot(input, index))
			quot = 0; /* Se cierra el quot */
		else if (!quot && is_quot(input, index))
			quot = input[index]; /* Se abre el quot */

		/* Si encontramos una barra y no esta entre comillas, hemos encaontrado un comando */
		if (input[index] == '|' && !quot)
		{
			/* TODO: Añadir comando */
			res = add_command(index - 1, input, res);
			if (!res)
				return (NULL);
		}
		index++;
	}
	return (res);
}

void	parse(t_msh *data)
{
	char	**division;

	/* TODO: Expandimos las variables ue hacen falta */

	/* TODO: dividir cada parte en los comandos que tengan */
	division = split_commands(data->input);

	int index = -1;
	while (division[++index])
		printf("=> CMD(%d): [%s]\n", index, division[index]);


	/* TODO: para cada comando, obtener los infiles */

	/* TODO: para cada comando, obtener los outfiles */

	/* TODO: para cada comando, obtener el comando principal y las flags/argumentos  que se le añaden */

}