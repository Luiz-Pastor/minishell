#include "../../inc/minishell.h"
	// cambiar el pwd actual y el pwd anterior 
	// el resto de cosas las hace en plan a
	// primero buscar si e pdw al que intento acceder exista 
	// solo te pilla el primer argumento el resto lo ignora
	// en el caso de que exista entonces tengo que actualizrlo el resto de comando se ejecutan con el exeve eese ni se como
	// se inicia sin old pwd hay que crearlo la primera vez que te mueves	// ver si el comando e cd . cd .. o cd el cd . se qued en el directory que esta el cd .. va uno hacia atras el cd y un path va hacia el path el cd y el cd y una carpeta se va a la carpeta 
	// if (search_directory() == 1)
	// {
	// 	// haz cosas puto
	// }
	// else
	// 	printf("no se encontro el directorio al que intentas acceder\n");
	// return ;

// char	*build_new_pwd()
// {

// }

// int	search_directory(t_msh *msh)
// {
// 	char *directory;
// 	int i;

// 	i = 0;
// 	while (msh->envp[i])
// 	{
// 		if (ft_strncmp(msh->envp[i], "PWD=", 4));
// 			break ;
// 		i++;
// 	}
// 	directory = ft_strjoin(msh->envp[i], "/");
// }




/*
	SI EXISTE PWD EN ENV:
		-> Si el nuevo directorio existe, actualizar PWD y crear OLDPWD, con el path anterior
		-> Si el nuevo directorio no existe, no modificar nada
	SI NO EXISTE PWD EN ENV
		-> Si se cambia el directorio, NOPWD = antigua carpeta y no se actualiza PWD
		-> Si no exte, no se modifica nada
*/

static void	error_cd(t_msh *msh, char *old, char *new, char *msg)
{
	msh->last_out = 1;
	ft_mfree(2, &old, &new);

	if (!msg)
		perror("msh: cd");
	else
		printf("%s\n", msg);
}

static char	*get_target(t_msh *msh, t_cmd *cmd)
{
	int		index;
	char	*res;
	
	/* Si hay argumentos, cogemos el primero */
	if (matrix_length(cmd->arguments))
	{
		res = ft_strdup(cmd->arguments[0]);
		if (!res)
			exit_malloc();
		return (res);
	}
	
	/* Si no hay argumentos, copiamos la varable HOME */
	index = search_envp(msh->envp, "HOME");

	/* Si no esta home, error y a otra cosa */
	if (index < 0)
	{
		error_cd(msh, NULL, NULL, "msh: cd: HOME not set");
		return (NULL);
	}

	/* Si sí que existe, hago una copia y lo devuelvo */
	res = ft_strdup(&msh->envp[index][5]);
	if (!res)
		exit_malloc();
	return (res);
}

static void	update_env(t_msh *msh, char *old, char *new)
{
	int	index;
	char	*new_pwd;
	
	/* Actualizamos PWD si existe */
	index = search_envp(msh->envp, "PWD");
	if (index >= 0)
	{
		new_pwd = ft_strjoin("PWD=", new);
		if (!new_pwd)
			exit_malloc();
		free(msh->envp[index]);
		msh->envp[index] = new_pwd;
	}

	/* Actualiamos o creamos PWD */
	index = search_envp(msh->envp, "OLDPWD");
	if (index == -1)
	{
		msh->envp = insert_envp(msh->envp, old);
		if (!msh->envp)
			exit_malloc();
	}
	else
	{
		/* Existe OLDPWD, actualizamos */
		change_envp(msh->envp, "OLDPWD", new);
	}
}

void	bd_cd(t_msh *msh, int nb_comand)
{	
	char	*new_path;
	char	*old_path;
	t_cmd *current = &msh->cmds[nb_comand];

	/* Nos guardamos el path hacia el que vamos */
	new_path = get_target(msh, current);
	if (!new_path)
		return ;

	/* No guardamos el antiuo PATH, por si hay que actualizar despues datos */
	old_path = getcwd(NULL, 0);

	/* Nos intentamos mover, si hay algun error, seteamos el res a 1 */
	if (chdir(new_path) < 0)
		return (error_cd(msh, old_path, new_path, NULL));
	
	/* Si estamos aqui, nos hemos movido de directorio */
	msh->last_out = 0;
	
	/* Cambiamos las variables de entorno:
		-> PWD=new_path si es que existia antes; sino nada
		-> OLDPATH=lo que habia en PATH, o old_path
	*/
	update_env(msh, old_path, new_path);

	free(new_path);

	return ;
}
