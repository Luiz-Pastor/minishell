#include "../../inc/minishell.h"

/* TODO: hace cosas raretas */
static int	is_full_path(t_cmd *cmds)
{
	if (cmds->main[0] == '/')
		return (1);
	if (!ft_strncmp(cmds->main, "../", 3))
		return (1);
	if (!ft_strncmp(cmds->main, "./", 2))
		return (1);
	return (0);
}

static char	*build_path(t_cmd *cmds, char **path_list)
{
	int		i;
	char	*path;

	i = 0;
	/* si no hay posibles rutas o si el cmd que nos pasan tiene una ruta le decimos que nuestro path sera el arguento que nos pasan como cmd */
	if (path_list == NULL || is_full_path(cmds) == 1)
		path = ft_strdup(cmds->main);
	else
	{
		/* Si tenemos posibles rutas iteramos sobre ellas viendo si esta el cmd dentro de esas rutas*/
		while (path_list[i])
		{
			path = ft_strdup(path_list[i]);
			if (!path)
				return (NULL);
			path = ft_gnl_strjoin(path, "/"); 
			if (!path)
				return (NULL);
			path = ft_gnl_strjoin(path, cmds->main);
			if (!path)
				return (NULL);
			/* Cuando encuentra el cmd en una carpeta salimos con la ruta ya guardada*/
			if (access(path, F_OK) == 0)
				break ;
			free(path);
			i++;
		}
	}
	return (path);
}

static char	**get_path_list(char **envp)
{
	char	**path_list;
	int		i;

	if (envp[0] == NULL)
		path_list = NULL;
	else
	{
		i = 0;

		/* Buscamos si existe la variable path */
		while (envp[i] != NULL)
		{
			if (!ft_strncmp(envp[i], "PATH=", 5))
				break ;
			i++;
		}
		if (envp[i] == NULL)
			return (NULL); // si no existe la variable path
		
		/* Hacemos un split de la variable path ara sacar todas las posibles rutas en las que encontrar el cmd*/
		path_list = ft_split(&envp[i][5], ':');
		if (!path_list)
			return (NULL);
	}
	return (path_list);
}

char	*get_path(t_cmd *cmds, char **envp)
{
	char **path_list;
	char	*path_cmd;

	/* me guardo tods los posibles path mirar si existe la variable path y hacerle un split de esa linea por : */
	path_list = get_path_list(envp);
	printf("........... %s ...........\n", path_list[1]);
	/* si la variable path_list en nula podemos crear un posible path con el nombre del comando */

	/* construir el path de donde esta el cmd */
	path_cmd = build_path(cmds, path_list);
	if (!path_cmd)
		exit (1);
	printf("........... %s ...........\n", path_cmd);
	free(path_list);
	return (path_cmd);
}
