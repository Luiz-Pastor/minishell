#include "../../inc/minishell.h"

char	*get_variable(char *arguments)
{
	int		i;
	char	*variable;

	i = 0;
	while (arguments[i] != '\0' && arguments[i] != '=')
		i++;
	if (arguments[i] == '=')
		i++;
	variable = malloc(sizeof(char) * (i + 1));
	if (!variable)
		exit_malloc();
	i = 0;
	while (arguments[i] != '\0' && arguments[i] != '=')
	{
		variable[i] = arguments[i];
		i++;
	}
	if (arguments[i] == '=')
	{
		variable[i] = arguments[i];
		i++;
	}
	variable[i] = '\0';
	return (variable);
}

char	*get_content(char *arguments)
{
	int		i;
	char	*content;
	int		aux;
	int		size;

	i = 0;
	while (arguments[i] != '\0' && arguments[i] != '=')
		i++;
	if (arguments[i] == '=')
		i++;
	aux = i;
	size = 0;
	while (arguments[i] != '\0')
	{
		size++;
		i++;
	}
	content = malloc(sizeof(char) * (size + 1));
	if (!content)
		exit_malloc();
	size = 0;
	while (arguments[aux] != '\0')
		content[size++] = arguments[aux++];
	content[size] = '\0';
	return (content);
}

t_bool	check_if_variable_ok(char *arguments)
{
	int	i;

	i = 0;
	if (arguments[i] && ft_correct_var_char(arguments[i], FIRST_LETTER) == 1)
	{
		i++;
		while (arguments[i] != '\0' && (ft_correct_var_char(arguments[i],
					MID_LETTER) == 1 || arguments[i] == '='))
		{
			if (arguments[i] == '=')
				return (TRUE);
			i++;
		}
	}
	return (FALSE);
}

char	**replace_content(t_msh *msh, char *variable, char *content)
{
	int	i;

	i = 0;
	while (msh->envp[i] != NULL)
	{
		if (!ft_strncmp(msh->envp[i], variable, ft_strlen(variable)))
		{
			free(msh->envp[i]);
			msh->envp[i] = ft_strjoin(variable, content);
			if (!msh->envp)
				exit_malloc();
			break ;
		}
		i++;
	}
	return (msh->envp);
}

t_bool	check_if_var_exist(t_msh *msh, char *variable)
{
	int	i;

	i = 0;
	while (msh->envp[i] != NULL)
	{
		if (!ft_strncmp(msh->envp[i], variable, ft_strlen(variable)))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
