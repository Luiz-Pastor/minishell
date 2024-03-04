#include "../inc/minishell.h"

int		g_signal_control;

void	leaks(void)
{
	system("leaks -q minishell");
}

int	main(int argc, char *argv[], char *envp[])
{
	t_msh	*data;

	g_signal_control = 0;
	if (argc != 1)
		return (printf("%s Try: %s\n", ERROR_MSG, argv[0]));
	data = init_msh(envp);
	if (!data)
		exit_malloc();
	if (manage(data))
		exit_malloc();
	free_msh(data);
	return (0);
}
