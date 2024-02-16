#include "../../inc/minishell.h"

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
void	bd_cd(t_msh *msh, int nb_comand)
{
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
	(void)msh;
	(void)nb_comand;
	chdir("..");
	// actualizar le pwd
	// meter el old pwd
	return ;
}