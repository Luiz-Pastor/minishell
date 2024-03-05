#include "../inc/minishell.h"

static void	free_cmds(t_msh *data)
{
	int	index;
	int	j;

	index = -1;
	while (++index < data->cmds_count)
	{
		free_parts(data->cmds[index].main, data->cmds[index].input);
		data->cmds[index].main = NULL;
		data->cmds[index].input = NULL;
		free_parts(NULL, data->cmds[index].arguments);
		data->cmds[index].arguments = NULL;
		j = -1;
		while (++j < data->cmds[index].infiles_count)
			ft_mfree(1, &data->cmds[index].infiles[j].name);
		j = -1;
		while (++j < data->cmds[index].outfiles_count)
			ft_mfree(1, &data->cmds[index].outfiles[j].name);
		ft_mfree(2, &data->cmds[index].infiles, &data->cmds[index].outfiles);
		free(data->cmds[index].complete_cmd);
		data->cmds[index].complete_cmd = NULL;
	}
	printf("Libero\n");
	ft_mfree(2, &data->input, &data->cmds);
}

static int	is_input_empty(char *input)
{
	int	index;

	index = 0;
	if (!input)
		return (1);
	while (input[index])
	{
		if (!is_space(input[index]))
			return (0);
		input++;
	}
	return (1);
}

static void	manage_exec(t_msh *data)
{
	data->executing = 1;
	if (data->here_doc_flag == 2)
		g_signal_control = 2;
	else
		g_signal_control = 1;
	executor(data);
	if (g_signal_control == 131)
		data->last_out = 131;
	g_signal_control = 0;
	data->executing = 0;
	free_cmds(data);
}

static void	manage_readline(t_msh *data)
{
	data->input = readline("UwUshell> ");
	if (!data->input)
	{
		rl_replace_line("", 0);
		printf("exit\n");
		exit(0);
	}
}

int	manage(t_msh *data)
{
	signals_manage(data);
	ctrl_c_disable();
	while (1)
	{
		manage_readline(data);
		if (is_input_empty(data->input))
		{
			free(data->input);
			continue ;
		}
		data->input = check_quots(data);
		if (!data->input)
		{
			check_error(data);
			continue ;
		}
		add_history(data->input);
		if (!parse(data))
		{
			check_error(data);
			continue ;
		}
		manage_exec(data);
	}
	return (0);
}
