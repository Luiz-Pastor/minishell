#include "../../inc/minishell.h"

# define FIRST_LETTER 1
# define MID_LETTER 2

char	**order_alf_envp2(char **new_envp)
{
	char	*aux;
	int		i;
	int		j;

	i = 0;
	while (new_envp[i])
	{
		j = i + 1;
		while (new_envp[j])
		{
			if (ft_strcmp(new_envp[i], new_envp[j]) > 0)
			{
				aux = new_envp[i];
				new_envp[i] = new_envp[j];
				new_envp[j] = aux;
			}
			j++;
		}
		i++;
	}
	return(new_envp);
}

char	**order_alf_envp(char **envp)
{
	char	**new_envp;
	int		lines;
	int	i;

	i = -1;
	lines = 0;
	while (envp[++i])
		lines++;
	new_envp = malloc(sizeof(char*) * lines + 1);
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[i] = NULL;
	new_envp = order_alf_envp2(new_envp);
	new_envp[i] = NULL;
	return (new_envp);
}

void	export_alone(t_msh *msh)
{
	int	i;
	int	j;
	char	**order_envp;

	i = -1;
	order_envp = order_alf_envp(msh->envp);
	if (!order_envp)
		return ; // malloc error
	while (order_envp[++i])
	{
		j = 0;
		printf("declare -x ");
		while (order_envp[i][j] != '=' && order_envp[i][j] != '\0')
		{
			printf("%c", order_envp[i][j]);
			j++;
		}
		printf("%c\"", order_envp[i][j++]);
		while (order_envp[i][j] != '\0')
		{
			printf("%c", order_envp[i][j]);
			j++;
		}
		printf("\"\n");
	}
}

char	*get_variable(t_cmd	cmds)
{

}
char	*get_content(char *arguments)
{
	int i;

	i = 0;
	while (arguments[i] != '=')
	{
		if (arguments[i] = '\0')
			return (NULL);
	}
}

void	bd_export(t_msh *msh, int nb_comand)
{
	// int		i;
	// char	*aux;
	// int		size;

	printf("1 comando => [%s]\n", msh->cmds[nb_comand].main);
	if (!ft_strcmp(msh->cmds[nb_comand].main, "export") && msh->cmds->arguments == NULL)
	{
		// hay que tener cuidado luego al imprimir e envp por q puede ser que no tenga cntenido 
		export_alone(msh);
		return ;
	}
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "export") && msh->cmds->arguments != NULL)
	{
		char 	*variable;
		char	*content;
		int		i;

		i = 0;
		// si es export a a sale en export normal pero no en el env
		while (msh->cmds[nb_comand].arguments[i] != NULL)
		{
			variable = get_variable(msh->cmds[nb_comand]->arguments[i]);
			content = get_conntent(msh->cmds[nb_comand]);
			msh->envp = add_to_envp(msh, variable, content);
			i++;
		}
		// mirar si existe esa variable en ell caso de que exista hay que sobrescribir
		// hay que tener cuidado luego al imprimir e envp por q puede ser que no tenga cntenido y las variablles qe no tengan un = no se imrimen en ell envp


	}
	else
		return ; // no es export el comando;
	// i = 0;
	// aux = NULL;
	// // export
	// while (input[i] != '\0')
	// {
	// 	size = 0;
	// 	while (input[i] == ' ') // ignoramos los espacios
	// 		i++;
	// 	while (input[i] != ' ' && input[i] != '=') // tenemos que leer hasta encontrar un espacio o un = 
	// 	{
	// 		i++;
	// 		size++;
	// 	}
	// 	aux = ft_substr(input, i, size); // una temporal para ver si va a ser variable o no 
	// 	if (!aux)
	// 		return ; // malloc error
	// 	int j = 0;
	// 	if (aux && input[i] == '=')
	// 	{
	// 		if (ft_correct_var_char(aux[j], FIRST_LETTER) == 0);
	// 				perror("bash: export: (lo que ese mal) not a valid identifier");
	// 		i++;
	// 		while(aux[j] != '\0')
	// 		{
	// 			if (ft_correct_var_char(aux[j], MID_LETTER) == 0);
	// 				perror("bash: export: (lo que ese mal) not a valid identifier");
	// 			j++;
	// 		}
	// 		// si llega aqui es que lo siguiente que este justo pegado con o sin comillas va a ser el contenido de la variable 
	// 	}
	// 	else
	// 	{
	// 		free(aux);
	// 		aux = NULL;
	// 	}
	// 	// ª º \ $ _ letra_min letra_mayus
	// 	// no pueden tener ningun tipo de caracter especial en ningun momento
	// }
}

