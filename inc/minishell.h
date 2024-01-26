#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
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

/*
 * brief	Information about the infiles and outfiles
*/
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

	/* Input del usuario */
	char 	*input;


	/* Lista de comandos */
	t_cmd	*cmds;

	/* Futuras señales */
	/*...*/

	/* Salida del ultimo comando */
	int		last_out;
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


/* Init struct msh */
t_msh	*init_msh(char *envp[]);
void	*free_msh(t_msh *data);

/* Bucle */
void	manage(t_msh *data);

/* Expand */
char	*expand(t_msh *data);

#endif