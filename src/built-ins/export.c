#include "../../inc/minishell.h"

char	**add_to_envp(t_msh *msh, char *variable, char *content)
{
	char	*new_line;
	char	**new_envp;
	int		i;

	new_envp = NULL;
	new_line = ft_strjoin(variable, content);
	if (!new_line)
		return (NULL);
	i = 0;
	while (msh->envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (msh->envp[i] != NULL)
	{
		new_envp[i] = msh->envp[i];
		i++;
	}
	new_envp[i] = new_line;
	i++;
	new_envp[i] = NULL;
	free(msh->envp);
	return (new_envp);
}

void	bd_export(t_msh *msh, int nb_comand)
{
	char	*variable;
	char	*content;
	int		i;

	if (!ft_strcmp(msh->cmds[nb_comand].main, "export")
		&& msh->cmds->arguments == NULL)
		export_alone(msh);
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "export")
			&& msh->cmds->arguments != NULL)
	{
		i = 0;
		while (msh->cmds[nb_comand].arguments[i] != NULL)
		{
			if (check_if_variable_ok(msh->cmds[nb_comand].arguments[i]) == TRUE)
			{
				variable = get_variable(msh->cmds[nb_comand].arguments[i]);
				if (!variable)
					return ; // liberar cosas
				content = get_content(msh->cmds[nb_comand].arguments[i]);
				if (!content)
					return ; // liberar cosas
				if (check_if_var_exist(msh, variable) == TRUE)
					msh->envp = replace_content(msh, variable, content);
				else
					msh->envp = add_to_envp(msh, variable, content);
			}
			else
			{
				printf("%s", BAD_SYNTAX_EXPORT);
				break ;
			}
			i++;
		}
	}
	return ; // se sale si no es export el comando
}
