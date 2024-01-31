#include "../inc/minishell.h"

# define TEMP_FOLDER	"/tmp/"

static char	*check_ava_name(char *del)
{
	char	*checker[2];
	char	*try_text;
	int		try;
	char	*res;

	try = 1;
	while(1)
	{
		/* Convertimos el numero del intento en texto */
		try_text = ft_itoa(try);
		if (!try_text)
			return (NULL);

		/* Guardamos en una variable el nombre dle archivo completo */		
		checker[0] = ft_strjoin(TEMP_FOLDER, del);
		if (!checker[0])
			return (ft_mfree(1, &try_text));

		checker[1] = ft_strjoin(checker[0], try_text);
		ft_mfree(2, &try_text, &checker[0]);
		if (!checker[1])
			return (ft_mfree(1, &checker[0]));

		/* Miramos si el archivo exite; si no existe, hemos encontrado el anombre del archivo adecuado */
		if (access(checker[1], F_OK) == -1)
		{
			res = checker[1];
			break ;
		}

		/* El archivo existia; sumamos uno al try y eliminamos la memoria que quedaba */
		free(checker[1]);
		try++;
	}
	return (res);
}

static int	get_data(int fd, char *filename, char *del)
{
	char	*full_del;
	char	*buffer;

	/* Unimos un salto de linea al delimitador, para que el gnl lo detecte bien */
	full_del = ft_strjoin(del, "\n");
	if (!full_del)
		return (0);


	/* Leemos hasta que se encuentre el delimitador o ctrl+D */
	buffer = get_next_line(0);
	while (buffer && ft_strcmp(buffer, full_del))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(0);
	}
	if (buffer)
		free(buffer);
	return (1);
}

char	*here_doc(char *del)
{
	int		fd;
	char	*name;

	/* Obtenemos el nombre del archivo donde guardar la información */
	name = check_ava_name(del);
	if (!name)
		return (NULL);

	/* Abrimos el archivo */
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		free(name);
		return (NULL);
	}

	/* Pedimos los datos al usuario */
	if (!get_data(fd, name, del))
	{
		/* Error al leer del usuario o por memoria */
		free(name);
		close(fd);
		return (NULL);
	}

	/* Cerramos el archivo de escritura y devolvemos el nombre del archivo */
	close(fd);
	return (name);
}
