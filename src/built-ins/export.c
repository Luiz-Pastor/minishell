#include "../../inc/minishell.h"

static char	**add_to_envp(t_msh *msh, char *variable, char *content)
{
	char	*new_line;
	char	**new_envp;
	int		i;

	new_envp = NULL;
	new_line = ft_strjoin(variable, content);
	if (!new_line)
		exit_malloc();
	i = 0;
	while (msh->envp[i] != NULL)
		i++;
	new_envp = malloc(sizeof(char *) * (i + 2));
	if (!new_envp)
		exit_malloc();
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

static void	do_ok_var(t_msh *msh, int nb_comand, int i)
{
	char	*variable;
	char	*content;

	variable = get_variable(msh->cmds[nb_comand].arguments[i]);
	if (!variable)
		exit_malloc();
	content = get_content(msh->cmds[nb_comand].arguments[i]);
	if (!content)
		exit_malloc();
	if (check_if_var_exist(msh, variable) == TRUE)
		msh->envp = replace_content(msh, variable, content);
	else
		msh->envp = add_to_envp(msh, variable, content);
}

static void	manage_export(t_msh *msh, int nb_comand, int i)
{
	while (msh->cmds[nb_comand].arguments[i] != NULL)
	{
		if (check_if_variable_ok(msh->cmds[nb_comand].arguments[i]) == TRUE)
			do_ok_var(msh, nb_comand, i);
		else
		{
			msh->last_out = 1;
			printf("uwu: export: '%s': not a valid identifier\n",
				msh->cmds[nb_comand].arguments[i]);
			break ;
		}
		i++;
	}
}

void	bd_export(t_msh *msh, int nb_comand)
{
	msh->last_out = 0;
	if (!ft_strcmp(msh->cmds[nb_comand].main, "export")
		&& msh->cmds[nb_comand].arguments == NULL)
		export_alone(msh);
	else if (!ft_strcmp(msh->cmds[nb_comand].main, "export")
		&& msh->cmds[nb_comand].arguments != NULL)
		manage_export(msh, nb_comand, 0);
	return ;
}
