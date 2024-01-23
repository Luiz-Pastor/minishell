#include "../inc/minishell.h"

# define FIRST_LETTER 1
# define MID_LETTER 2

// int	ft_correct_var_char(char c, int flag)
// {
// 	if (c == 'º')
// 		return (1);
// 	else if (c == '\\')
// 		return (1);
// 	else if (c == 'ª')
// 		return (1);
// 	else if (c == '_')
// 		return (1);
// 	else if (ft_isalpha(c) == 1)
// 		return (1);
// 	if (flag == MID_LETTER && ft_isdigit(c) == 1)
// 		return (1);
// 	if (flag == MID_LETTER && c == '$')
// 		return (1);
// 	// los numeros son validos siempre y cuando no esten el primero 
	
// 	return (0);
// }
void	ft_export(char *input)
{
	int		i;
	char	*aux;
	int		size;

	i = 0;
	aux = NULL;
	// export
	while (input[i] != '\0')
	{
		size = 0;
		while (input[i] == ' ') // ignoramos los espacios
			i++;
		while (input[i] != ' ' && input[i] != '=') // tenemos que leer hasta encontrar un espacio o un = 
		{
			i++;
			size++;
		}
		aux = ft_substr(input, i, size); // una temporal para ver si va a ser variable o no 
		if (!aux)
			return ; // malloc error
		int j = 0;
		if (aux && input[i] == '=')
		{
			if (ft_correct_var_char(aux[j], FIRST_LETTER) == 0);
					perror("bash: export: (lo que ese mal) not a valid identifier");
			i++;
			while(aux[j] != '\0')
			{
				if (ft_correct_var_char(aux[j], MID_LETTER) == 0);
					perror("bash: export: (lo que ese mal) not a valid identifier");
				j++;
			}
			// si llega aqui es que lo siguiente que este justo pegado con o sin comillas va a ser el contenido de la variable 
		}
		else
		{
			free(aux);
			aux = NULL;
		}
		// ª º \ $ _ letra_min letra_mayus
		// no pueden tener ningun tipo de caracter especial en ningun momento
	}
}