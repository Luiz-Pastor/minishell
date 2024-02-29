#include "../../inc/minishell.h"

static char	*content_var(char *variable, t_msh *data)
{
	int		i;
	char	*content;

	content = NULL;
	i = 0;
	if (data->envp[0] == NULL)
		return (NULL);
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], variable, ft_strlen(variable)))
			break ;
		i++;
	}
	if (data->envp[i])
	{
		content = ft_substr(data->envp[i], ft_strlen(variable),
				ft_strlen(data->envp[i]) - ft_strlen(variable));
		if (!content)
			exit_malloc();
	}
	else
		return (ft_strdup(""));
	return (content);
}

static char	*mod_infile_expand(t_msh *data, char *content, char *variable,
		int i)
{
	int		size;
	char	*new_input;
	int		j;
	int		z;
	int		aux;

	size = (ft_strlen(data->input) - (ft_strlen(variable) - 1)
			+ ft_strlen(content));
	new_input = malloc(sizeof(char) * size + 1);
	if (!new_input)
		exit_malloc();
	j = 0;
	z = 0;
	aux = 0;
	while (aux < i - 1)
		new_input[j++] = data->input[aux++];
	while (content[z] != '\0')
		new_input[j++] = content[z++];
	aux += ft_strlen(variable);
	while (data->input[aux] != '\0')
		new_input[j++] = data->input[aux++];
	new_input[j] = '\0';
	free(data->input);
	return (new_input);
}

char	*last_state(t_msh *data, int *i)
{
	char	*variable;
	char	*content;

	variable = ft_strdup("?");
	if (!variable)
		exit_malloc();
	variable = ft_gnl_strjoin(variable, "=");
	if (!variable)
		exit_malloc();
	content = ft_itoa(data->last_out);
	if (!content)
		exit_malloc();
	data->input = mod_infile_expand(data, content, variable, *i);
	if (!data->input)
		exit_malloc();
	*i += ft_strlen(content) - ft_strlen(variable);
	free_expand(variable, content);
	return (data->input);
}

void	*expand_var(t_msh *msh, int *i, int aux)
{
	char	*variable;
	char	*content;

	while (ft_correct_var_char(msh->input[*i], MID_LETTER) == 1)
		(*i)++;
	variable = ft_substr(msh->input, aux, (size_t)(*i) - aux);
	if (!variable)
		exit_malloc();
	variable = ft_gnl_strjoin(variable, "=");
	if (!variable)
		exit_malloc();
	content = content_var(variable, msh);
	if (!content)
		exit_malloc();
	msh->input = mod_infile_expand(msh, content, variable, aux);
	if (!msh->input)
		exit_malloc();
	*i += ft_strlen(content) - ft_strlen(variable) - 1;
	free_expand(variable, content);
	return (msh->input);
}
