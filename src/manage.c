#include "../inc/minishell.h"
#include <string.h>

void	print_data(t_msh *data)
{
	printf("\nNumero de comandos: %d\n", data->cmds_count);
	int index = 0;
	while (index < data->cmds_count)
	{
		int j;
		printf("--> MAIN: [%s]\n", data->cmds[index].main);
		
		j = 0;
		printf("\tArguments:\n");
		while (data->cmds[index].arguments && data->cmds[index].arguments[j])
			printf("\t\t· [%s]\n", data->cmds[index].arguments[j++]);
		
		j = 0;
		printf("\tMain + Arguments:\n");
		while (data->cmds[index].complete_cmd && data->cmds[index].complete_cmd[j])
			printf("\t\t· [%s]\n", data->cmds[index].complete_cmd[j++]);

		j = 0;
		printf("\tInfiles (%d):\n", data->cmds[index].infiles_count);
		while (j < data->cmds[index].infiles_count)
		{
			printf("\t\t-> {[%s], %d}\n", data->cmds[index].infiles[j].name, data->cmds[index].infiles[j].type);
			j++;
		}
		j = 0;
		printf("\tOutfiles (%d):\n", data->cmds[index].outfiles_count);
		while (j < data->cmds[index].outfiles_count)
		{
			printf("\t\t-> {[%s], %d}\n", data->cmds[index].outfiles[j].name, data->cmds[index].outfiles[j].type);
			j++;
		}
		printf("\n==============================================\n\n");
		index++;
	}
}

static void	free_cmds(t_msh *data)
{
	int	index;
	int	j;
	index = -1;
	while (++index < data->cmds_count)
	{
		free_parts(data->cmds[index].main, data->cmds[index].input);
		free_parts(NULL, data->cmds[index].arguments);
		j = -1;
		while (++j < data->cmds[index].infiles_count)
			free(data->cmds[index].infiles[j].name);
		j = -1;
		while (++j < data->cmds[index].outfiles_count)
			free(data->cmds[index].outfiles[j].name);
		ft_mfree(2, &data->cmds[index].infiles, &data->cmds[index].outfiles);
	}
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

int	manage(t_msh *data)
{
	signals_manage(data);
	ctrl_c_disable();
	while (1)
	{
		data->input = readline("UwUshell> ");
		if (!data->input)
		{
			rl_replace_line("", 0);
        	printf("exit\n");
			exit(0);
		}
		if (is_input_empty(data->input))
			continue ;
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
		data->executing = 1;
		signal_control = 1;
		executor(data);
		signal_control = 0;
		data->executing = 0;
		// print_data(data);
		free_cmds(data);
	}
	return (0);
}
