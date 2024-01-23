#include "../inc/minishell.h"

#define	QUOTE_MSG C_CYAN"dquote> "CLEAR

static char	*dquote(char *input)
{
	char	*new_line;
	char	*inter;
	char	*full;

	new_line = readline(QUOTE_MSG);
	if (!new_line)
		return (ft_mfree(1, &input));

	inter = ft_strjoin(input, "\n");
	if (!inter)
		return (ft_mfree(1, &input));

	full = ft_strjoin(inter, new_line);
	if (!full)
		return (ft_mfree(2, &input, &new_line));

	ft_mfree(3, &input, &inter, &new_line);

	return (full);
}

static int	next_quot(char *input, int i)
{
	char	ch;

	ch = input[i];
	while (input[++i])
	{
		if (input[i] == ch && input[i] == '\'')
			return (i);
		if (input[i] == ch && input[i-1] != '\\' && ch == '\"')
			return (i);
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
		if ((input[i] == '\'' || input[i] == '\"') && (i == 0 || input [i-1] != '\\'))
		{
			next = next_quot(input, i);
			if (next == -1)
			{
				/* Pedir más input */
				input = dquote(input); 
				if (!input)
					return (NULL);
				i = -1;
			}
			else
				i = next;
		}
		i++;
	}
	return (input);
}
