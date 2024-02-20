#include "../inc/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void) argv;
	t_msh	*data;

	if (argc != 1)
		return (printf("%s\n", ERROR_MSG));
	data = init_msh(envp);
	if (!data)
		exit_malloc();
	if (manage(data))
		exit_malloc();
	free_msh(data);
	return (0);
}
