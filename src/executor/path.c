#include "../../inc/minishell.h"

// int	is_full_path(t_data *data)
// {
// 	if (data->command[0][0] == '/')
// 		return (1);
// 	if (!ft_strncmp(data->command[0], "../", 3))
// 		return (1);
// 	if (!ft_strncmp(data->command[0], "./", 2))
// 		return (1);
// 	return (0);
// }

// static char	*build_path(t_data *data)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	if (data->path_list == NULL || is_full_path(data) == 1)
// 		path = ft_strdup(*data->command);
// 	else
// 	{
// 		while (data->path_list[i])
// 		{
// 			path = ft_strdup(data->path_list[i]);
// 			if (!path)
// 				return (free_split(data->path_list, data->command));
// 			path = ft_strjoin(path, "/");
// 			if (!path)
// 				return (free_split(data->path_list, data->command));
// 			path = ft_strjoin(path, data->command[0]);
// 			if (!path)
// 				return (free_split(data->path_list, data->command));
// 			if (access(path, F_OK) == 0)
// 				break ;
// 			i++;
// 		}
// 	}
// 	return (path);
// }
char	*get_path(t_cmd *cmds, char **envp)
{
	char **path_list;
	char	*path_cmd;

	/* me guardo tods los posibles path mirar si existe la variable path y hacerle un split de esa linea por :*/
	path_list = get_path_list();
	if (!path_list)
		exit (1);
	/* construir el path de donde esta el cmd */
	path_cmd = build_path();
	if (!path_cmd)
		exit (1);
	return (path_cmd);
}