#include "../inc/minishell.h"

# define FIRST_LETTER 1
# define MID_LETTER 2

typedef struct	s_quotes
{
	int		flag;
	char	type;
}				t_quotes;

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
			break ;
		i++;
	}
	if (data->envp[i])
	{
		content = ft_substr(data->envp[i], ft_strlen(variable), ft_strlen(data->envp[i]) - ft_strlen(variable));
		if (!content)
			return (NULL);
	}
	else
		return (NULL);
	return (content);
}

int	ft_correct_var_char(char c, int flag) // esta funcion esta duplicada en el export
{
	if (c == '\\')
		return (1);
	else if (c == '_')
		return (1);
	else if (ft_isalpha(c) == 1)
		return (1);
	else if (flag == MID_LETTER && ft_isdigit(c) == 1)
		return (1);
	else
		return (0);
	// los numeros son validos siempre y cuando no esten el primero 
}

// NOTE: prblemmas angie futuro: algun $ mas?¿?¿?
// flag de si estan abiertas las comillas  no 
// {}
// $ espacio
// $?
// variables solo pueden empezar por letra y tener numeros
// al generar la variable mete el =
char	*mod_infile_expand(t_msh *data, char *content, char *variable, int i)
{
	// variable + $ es el valor a sustituir por content en el input
	int		size;
	char	*new_input;
	int		j;
	int		z;
	int		aux;

	size = (ft_strlen(data->input) - (ft_strlen(variable) - 1) + ft_strlen(content));
	new_input = malloc (sizeof(char) * size + 1);
	if (!new_input)
		return (NULL);
	printf("size --> %d\n", size);
	j = 0;
	z = 0;
	aux = 0;
	while (aux < i - 1)
	{
		new_input[j] = data->input[aux];
		aux++;
		j++;
	}
	while (content[z] != '\0')
	{
		new_input[j] = content[z];
		j++;
		z++;

	}
	aux += ft_strlen(variable) + 1;
	 while (data->input[aux] != '\0')
	{
		new_input[j] = data->input[aux];
		aux++;
		j++;
	}
	printf("owo\n");
	new_input[j] = '\0';
	free(data->input);
	return(new_input);
}

static char	*last_state(t_msh *data, int *i)
{
	char	*variable;
	char	*content;

	variable = ft_strdup("?");
	if (!variable)
		return (NULL); // malloc error 
	content = ft_itoa(data->last_out);
	if (!content)
		return (NULL); // malloc error 
	data->input = mod_infile_expand(data, content, variable, *i);
	*i += ft_strlen(content) - ft_strlen(variable);
	free(content);
	free(variable);
	return (data->input);
}

static char	*expand_manage(t_msh *data, t_quotes *quotes, int *i)
{
	char	*variable;
	char	*content;
	int		aux;

	// tengo que quitar los corchetes de mierda
	if (quotes->flag == 1 && quotes->type == '\'' )
		return(data->input);
	aux = *i;
	if (data->input[*i] == '?')
		return (last_state(data, i));
	if (ft_correct_var_char(data->input[*i], FIRST_LETTER) == 1)
	{
		(*i)++;
		while(ft_correct_var_char(data->input[*i], MID_LETTER) == 1)
			(*i)++;
		printf("i - aux ----> %d\n", *i - aux);
		variable = ft_substr(data->input, aux, (size_t)*i - aux); // guardar en variable el = antes de mirarlo
		if (!variable)
			return (NULL); // malloc error
		variable = ft_gnl_strjoin(variable, "=");
		if(!variable)
			return (NULL);
		printf("variable ---> %s\n", variable);
		// buscar variable si no esta nada ignorar ni el siguiente espacio
		content = content_var(variable, data);
		if (!content)
			return (NULL); // error
		printf("contenido ---> %s\n", content);
		data->input = mod_infile_expand(data, content, variable, aux);
		if (!data->input)
			return (NULL);
		printf("supuesto resultado final %s\n", data->input);
		printf("bxbbuwu\n");
		// puede haber cosas justo despues pero solo un puntoo 
		*i += ft_strlen(content) - ft_strlen(variable);
		free(content);
		free(variable);
		printf(" i---> %d\n", *i);
	}
	//  la i cambia actualizarla a la ueva posicion donde seguir iterando en la funcion expand
	return (data->input);
}

char	*expand(t_msh *data)
{
	t_quotes	quotes; // flag para saber si hay comillas o no 
	// No hay nada abierto ->			 Se interpreta ->    /Users… 0
	// Hay comillas dobles abiertas->    Se interpreta ->    /Users/… 0
	// Hay comillas simples abiertas ->  No se interpreta -> $PATH  1
	int		i;

	i = 0;
	quotes.flag = 0;
	quotes.type = '0';
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '\'' || (data->input[i] == '\"' && (i == 0 || data->input[i - 1] != '\\')))
		{
			/* TODO: Comprobar si está abierta -> si se puede cerrar */
			if (quotes.flag == 1 && quotes.type == data->input[i])
			{
				quotes.flag = !quotes.flag;
				quotes.type = 0;
			}
			else if (quotes.flag == 0) /* Si esta cerrada, se abre */
			{
				quotes.flag = !quotes.flag; // 0 esta cerrado 1 esta abierto
				quotes.type = data->input[i]; // que comillas son las que estan abiertas 
			}
			i++;
		}
		if (data->input[i] == '$')
		{
			i++;
			data->input = expand_manage(data, &quotes, &i);
			if (!data->input)
				return (NULL); // malloc error
		}
		i++;
	}
	return (data->input);
}
