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

enum
{
	WITH_QUOT = 0,
	WITHOUT_QUOT
};

typedef enum
{
	INFILE = 0,
	HERE_DOC,
	TRUNC,
	APPEND
} t_file_type;

typedef	enum
{
	NONE = 0,
	MALLOC,
	CTR_D,
	SYNTAX
} t_error;


struct s_msh
{

	char	*input;

	/* Variables de entorno. Se acualiza */
	char	**envp;

	/* Lista de comandos */
	t_cmd	*cmds;
	int		cmds_count;

	/* Futuras señales */
	/*...*/

	/* Salida del ultimo comando */
	int		last_out;

	/* Último error */
	t_error	error;
};

struct s_cmd
{
	/* Input divisido por bloques */
	char **input;

	/* Comando sin flags */
	char	*main;

	/* Argumentos (y flags) del comando*/
	char	**arguments;

	/* Archivos infile */
	t_io_file *infiles;
	int			infiles_count;

	/* Archivos outfile */
	t_io_file *outfiles;
	int			outfiles_count;
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
int		manage(t_msh *data);

/* Parser */
char	*check_quots(t_msh *msh);

char	**divide_cmd_args(char *input, int);

/* Matrix utils*/
char	**add_part(char *str, char **mtx);
void	*free_parts(char *part, char **args);
int	matrix_length(char **mtx);

/* Quot utils */
int	is_quot(char *input, int index);

/* Utils */
int	is_space(char ch);

/* Parser */
void	*parse(t_msh *msh);
void	*create_commands(t_msh *msh);

void	*add_infile(t_file_type type, char *name, t_cmd *cmd, t_msh *msh);
void	*add_outfile(t_file_type type, char *name, t_cmd *cmd, t_msh *msh);
void	*check_command(char *input, t_cmd *cmd, t_msh *msh);
void	*check_argument(char *input, t_cmd* cmd, t_msh *msh);


/* Errores */
void	*set_error(t_error error, t_msh *msh);
void	check_error(t_msh *msh);
int		is_error(t_msh *msh);

#endif