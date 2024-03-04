#include "../../inc/minishell.h"

void	auxiliar_error_open(int *error, char *msg)
{
	perror(msg);
	*error = 1;
}
