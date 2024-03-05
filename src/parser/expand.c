#include "../../inc/minishell.h"

static char	*expand_manage(t_msh *msh, t_quotes *quotes, int *i)
{
	int	aux;

	if (msh->input[*i] == '$' && msh->input[*i + 1])
		(*i)++;
	aux = *i;
	if (quotes->flag == 1 && quotes->type == '\'')
		return (msh->input);
	if (msh->input[*i] == '?')
		return (last_state(msh, i));
	if (ft_correct_var_char(msh->input[*i], FIRST_LETTER) == 1)
	{
		(*i)++;
		msh->input = expand_var(msh, i, aux);
	}
	return (msh->input);
}

static void	manage_quotes(t_quotes *quotes, char c)
{
	if (quotes->flag == 1 && quotes->type == c)
	{
		quotes->flag = !quotes->flag;
		quotes->type = 0;
	}
	else if (quotes->flag == 0)
	{
		quotes->flag = !quotes->flag;
		quotes->type = c;
	}
}

char	*expand(t_msh *data)
{
	int			i;
	t_quotes	quotes;

	i = 0;
	quotes.flag = 0;
	quotes.type = '0';
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '\'' || (data->input[i] == '\"' && (i == 0
					|| data->input[i - 1] != '\\')))
			manage_quotes(&quotes, data->input[i]);
		if (data->input[i] == '$')
		{
			data->input = expand_manage(data, &quotes, &i);
			if (!data->input)
				exit_malloc();
		}
		i++;
	}
	return (data->input);
}
