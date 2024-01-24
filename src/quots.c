#include "../inc/minishell.h"

#define	QUOTE_MSG C_CYAN"dquote> "CLEAR

static int	is_quot(char *input, int index)
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

static char	*dquote(char *input)
{
	char	*new_line;
	char	*inter;
	char	*full;

	/* Leemos linea: si devueve NULL (ctr+D), liberamos memoria */
	new_line = readline("dquote> ");
	if (!new_line)
		return (ft_mfree(1, &input));

	/* Metemos un salto de linea a la info que teniamos */
	inter = ft_strjoin(input, "\n");
	if (!inter)
		return (ft_mfree(1, &input));

	/* Juntamos la linea+\n con ell nuevo texto */
	full = ft_strjoin(inter, new_line);
	if (!full)
		return (ft_mfree(2, &input, &new_line));

	/* Liberamos la memoria auxiliar */
	ft_mfree(3, &input, &inter, &new_line);

	/* Devolvemos la linea anterior + \n + la nueva lectura */
	return (full);
}

static int	next_quot(char *input, int i)
{
	char	ch;

	/* Nos guardamos el caracter po el que empieza la string, y buscamos el siguiente */
	ch = input[i];
	while (input[++i])
	{
		if (input[i] == ch && is_quot(input, i))
			return i;
	}
	return (-1);
}



/*
	- Id. A: al encontrar una comilla iterar hasta encontrar la otra
*/
char	*check_quots(char *input)
{
	int	i;
	int next;

	i = 0;
	if (!input)
		return (NULL);
	while (input[i])
	{
		/* Para cada caracter miramos si es un quot */
		if (is_quot(input, i))
		{
			/*
				Si es quot, buscamos la siguiente ocurrecia:
					- Si no tiene ocurrencias, le pedimos al usuario mas texto y volvemos a comprobar
					- Si encontramos ocurrencia, miramos mas quots a partir del quot que finaliza
			*/
			next = next_quot(input, i);

			if (next == -1)
			{
				input = dquote(input); 
				/* ctl+D a la hora de leer mas info, o error de memoria */
				if (!input)
					return (NULL);
				i--;
			}
			else
				i = next;
		}
		i++;
	}
	/* Devolvemos la linea con las quots bien puestas */
	return (input);
}
