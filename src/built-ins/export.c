#include "../../inc/minishell.h"

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

char	**order_alf_envp(char **envp)
{
	char	**new_envp;
	int		lines;
	int	i;
	int	j;

	i = 0;
	lines = 0;
	while (envp[i])
	{
		lines++;
		i++;
	}
	new_envp = malloc(sizeof(char*) * lines + 1);
	if (!new_envp)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = envp[i];
		i++;
	}
	char	*aux;
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
	return (new_envp);
}

void	export_alone(t_msh *msh)
{
	int	i;
	int	j;
	char	**order_envp;

	i = 0;
	order_envp = order_alf_envp(msh->envp);
	if (!order_envp)
		return ; // malloc error
	while (order_envp[i])
	{
		j = 0;
		write(1, "declare -x ", 12);
		while (order_envp[i][j] != '=' && order_envp[i][j] != '\0')
		{
			write(1, &order_envp[i][j], 1);
			j++;
		}
		write(1, &order_envp[i][j++], 1);
		write(1, "\"", 1);
		while (order_envp[i][j] != '\0')
		{
			write(1, &order_envp[i][j], 1);
			j++;
		}
		write(1, "\"", 1);
		write(1, "\n", 1);
		i++;
	}
}

void	ft_export(t_msh *msh)
{
	// int		i;
	// char	*aux;
	// int		size;

	/* ============================= */
	char *str = malloc(7);
	strcpy(str, "export");
	msh->cmds[0].main = str;
	/* ============================= */

	printf("=> [%s]\n", msh->cmds[0].main);
	if (!ft_strcmp(msh->cmds[0].main, "export") && msh->cmds->arguments == NULL)
	{
		printf("uwu\n");
		export_alone(msh);
	}
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