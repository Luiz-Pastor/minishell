#include "../../inc/minishell.h"

void	bd_echo(t_msh *msh, int nb_comand)
{
	(void)msh;
	(void)nb_comand;
	return ;
}
// int	main(int argc, char *argv[], char *envp[])
// {
// 	if (argc < 4)
// 		return(write(1, "invalid argrs\n", 15));
// 	if (ft_strcmp(argv[1], "echo"))
// 		return (1);
// 	char **cmd;

// 	cmd = malloc (sizeof(char*) * argc);
// 	if (!cmd)
// 	return (0);
// 	printf("## [%s]\n", cmd[0]);
// 	int i = 1;
// 	int j = 0;
// 	while (argv[i])
// 	{
// 		cmd[j] = ft_strdup(argv[i]);
// 		i++;
// 		j++;
// 	}
// 	cmd[j] = NULL;
// 	int x = 0;

// 	while (cmd[x])
// 		printf("=> [%s]\n", cmd[x++]);
// 	execve("/bin/echo", cmd, envp);
// 	return (0);
	
// }