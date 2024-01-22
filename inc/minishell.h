#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"

/*
 * brief	Bool type
*/
typedef enum e_bool		t_bool;

/*
 * brief	The main minishell struct
*/
typedef struct s_msh	t_msh;

/*
 * brief	The command struct
*/
typedef struct s_cmd	t_cmd;

typedef struct s_io_file	t_io_file;


enum e_bool
{
	FALSE = 0,
	TRUE
};

struct s_msh
{
	/* Variables de entorno. Se acualiza */
	char	**envp;

	/* Lista de comandos */
	t_cmd	*cmds;

	/* Futuras señales */
	/*...*/
};

struct s_cmd
{
	/* Comando con flags */
	char	*main;

	/* Archivos infile */
	t_io_file *infiles;

	/* Archivos outfile */
	t_io_file *outfiles;

	/* Next command with pipe */
	t_bool	pipe;
};

struct s_io_file
{
	char	*name;
	int		type;
};


// init msh
t_msh	*init_msh(char *envp[]);
void	*free_msh(t_msh *data);

#endif