#include "../../inc/minishell.h"

int	is_space(char ch)
{
	if (ch == ' ' || ch == '\n' || ch == '\t')
		return (1);
	if (ch == '\v' || ch == '\f' || ch == '\r')
		return (1);
	return (0);
}

char	*string_add(char *str, char ch)
{
	int	i;
	char *new;

	new = malloc(ft_strlen(str) + 2);
	if (!new)
		return (ft_mfree(1, &str));
	
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = ch;
	new[i + 1] = '\0';

	if (str)
		free(str);

	return (new);
}
