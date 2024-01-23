#include "../inc/minishell.h"

# define FIRST_LETTER 1
# define MID_LETTER 2

// como va esta puta mierda ._.

int	ft_correct_var_char(char c, int flag) // esta funcion esta duplicada en el export
{
	if (c == '\\')
		return (1);
	else if (c == '_')
		return (1);
	else if (ft_isalpha(c) == 1)
		return (1);
	if (flag == MID_LETTER && ft_isdigit(c) == 1)
		return (1);
	if (flag == MID_LETTER && c == '$')
		return (1);
	// los numeros son validos siempre y cuando no esten el primero 
	return (0);
}

char	*content_var(char *variable, t_msh *data)
{
	int i;
	char	*content;

	content = NULL;
	i = 0;
	if (data->envp[0] == NULL)
		return (NULL);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], variable, ft_strlen(variable)))
		{
			if (data->envp[i][ft_strlen(variable)] == '=')
				break ;
		}
		i++;
	}
	if (data->envp[i])
	{
		content = ft_substr(data->envp[i], ft_strlen(variable), ft_strlen(data->envp[i]) - ft_strlen(variable));
		if (!content)
			return (NULL);
	}
	return (content);
}
char	*mod_infile_expand(char *input, char *content, char *variable)
{
	// variable + $ es el valor a sustituir por content en el input
	int	size;
	char	*new_input;
	int		i;
	int		j;
	int		z;

	size = (ft_strlen(input) - (ft_strlen(variable) - 1) + ft_strlen(content));
	new_input = malloc (sizeof(char) * size + 1);
	if (!new_input)
		return (NULL);
	i = 0;
	j = 0;
	z = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			i++;
			if (!ft_strncmp(&input[i], variable, ft_strlen(variable)))
				i += ft_strlen(variable);
			while (content[z] != '\0')
			{
				new_input[j] = content[z];
				j++;
				z++;
			}
		}
		if (input[i])
			new_input[j] = input[i];
		j++;
		i++;
	}
	new_input[j] = '\0';
	free(input);
	return(new_input);
}
char *expand(char *input, t_msh *data)
{
	int		i;
	int		aux;
	char	*variable;
	char	*content;
	

	i = 0;
	while (input[i] != '\0')
	{
		// if (input[i] == '"');
		// if (input[i] == '\''); // las comillas simples se suponen que no permiten la expansion de variables pero no entiendo
		if (input[i] == '$')
		{
			i++;
			aux = i;
			if (input[i] == ' ')
				i++;
			else if (input[i] == '?')
			{
				variable = ft_strdup("?");
				printf("\nUwU\n");
				if (!variable)
					return (NULL); // malloc error 
					content = ft_itoa(data->last_out);
				if (!content)
					return (NULL); // malloc error 
				input = mod_infile_expand(input, content, variable);
				i += ft_strlen(content) - ft_strlen(variable);
				free(content);
				free(variable);
				printf("---> %d", i);
				// $? ultimo estado como ha salido el ultimo comando ejecutado
			}
			else if (input[i] == '$')
			{
				variable = ft_strdup("$");
				if (!variable)
					return (NULL); // malloc error 
				content = ft_strdup("NUMBER OF THE PID");
				if (!content)
					return (NULL); // malloc error 
				input = mod_infile_expand(input, content, variable);
				i += ft_strlen(content) - ft_strlen(variable);
				free(content);
				free(variable);
				printf("---> %d", i);
				// $$ pid del proceso de la terminal
			}
			else
			{
				while(ft_correct_var_char(input[i], MID_LETTER) == 1)
					i++;
				variable = ft_substr(input, aux, i - aux); // guardar en variable el = antes de mirarlo
				printf("---> %s\n", variable);
				if (!variable)
					return (NULL); // malloc error 
				// buscar variable si no esta nada ignorar ni el siguiente espacio
				content = content_var(variable, data);
				if (!content)
					return (NULL); // error
				input = mod_infile_expand(input, content, variable);
				// puede haber cosas justo despues pero solo un puntoo 
				i += ft_strlen(content) - ft_strlen(variable);
				free(content);
				free(variable);
				printf("---> %d\n", i);
			}
		}
		else 
			i++;
	}
	return (input);
}
