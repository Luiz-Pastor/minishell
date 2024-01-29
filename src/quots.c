#include "../inc/minishell.h"

#define	QUOTE_MSG C_CYAN"dquote> "CLEAR

/*  NOTE: si hay problema de lineas, sacar a funcion auxiliar aparte */
static char	*dquote(t_msh *msh)
{
	char	*new_line;
	char	*inter;
	char	*full;

	/* Leemos linea: si devueve NULL (ctr+D), liberamos memoria */
	new_line = readline("dquote> ");
	if (!new_line)
	{
		ft_mfree(1, &msh->input);
		return (set_error(CTR_D, msh));
	}

	/* Metemos un salto de linea a la info que teniamos */
	inter = ft_strjoin(msh->input, "\n");
	if (!inter)
	{
		ft_mfree(1, &msh->input);
		return (set_error(MALLOC, msh));
	}

	/* Juntamos la linea+\n con ell nuevo texto */
	full = ft_strjoin(inter, new_line);
	if (!full)
	{
		ft_mfree(2, &msh->input, &new_line);
		return (set_error(MALLOC, msh));
	}

	/* Liberamos la memoria auxiliar */
	ft_mfree(3, &msh->input, &inter, &new_line);

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
char	*check_quots(t_msh *msh)
{
	int	i;
	int next;

	i = 0;
	while (msh->input[i])
	{
		if (is_quot(msh->input, i))
		{
			next = next_quot(msh->input, i);
			if (next == -1)
			{
				msh->input = dquote(msh); 
				if (!msh->input)
					return (NULL);
				i--;
			}
			else
				i = next;
		}
		i++;
	}
	return (msh->input);
}
