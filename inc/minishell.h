#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# include <signal.h>
# include <string.h>
# include <termios.h>

# define TEMP_FOLDER	"/tmp/"

# define MALLOC_MSG C_RED"Malloc error"CLEAR
# define ERROR_MSG "Bad arguments input."
# define MINISHELL_MSG "minishell> "
# define ERROR_FORK_MSG "Fork"
# define ERROR_PIPE_MSG "Pipe"

extern int signal_control;

/*
 * brief	Bool type
*/
typedef enum e_bool			t_bool;

/*
 * brief	The main minishell struct
*/
typedef struct s_msh		t_msh;

/*
 * brief	The command struct
*/
typedef struct s_cmd		t_cmd;

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

typedef enum e_file_type
{
	INFILE,
	HERE_DOC,
	TRUNC,
	APPEND
}			t_file_type;

typedef enum e_error
{
	NONE = 0,
	CTR_D,
	SYNTAX,
	FORK,
	PIPE
}			t_error;

struct s_msh
{
	/* Variables de entorno. Se acualiza */
	char	**envp;

	/* Input del usuario */
	char	*input;

	/* Lista de comandos */
	t_cmd	*cmds;
	int		cmds_count;

	/* Salida del ultimo comando */
	int		last_out;
	int		executing;

	/* Flag para señales herdoc */
	int		here_doc_flag;

	/* stdin , stdout */
	int		cpy_stdin;
	int		cpy_stdout;
	int		cpy_last_in;
	int		cpy_last_out;

	/* ids  procesos*/
	pid_t	final_pid;
	int		last_status;

	/* Último error */
	t_error	error;
};

struct s_cmd
{
	/* Input divisido por bloques */
	char		**input;

	/* Comando sin flags */
	char		*main;

	/* Argumentos (y flags) del comando*/
	char		**arguments;

	/* Comando completo */
	char		**complete_cmd;
	
	/* Archivos infile */
	t_io_file	*infiles;
	int			infiles_count;

	/* Archivos outfile */
	t_io_file	*outfiles;
	int			outfiles_count;
};

struct s_io_file
{
	char	*name;
	int		type;
	char	*filename;
};

typedef struct s_quotes
{
	int		flag;
	char	type;
}				t_quotes;

/* Init struct msh */
t_msh	*init_msh(char *envp[]);
void	*free_msh(t_msh *data);

/* Bucle */
int		manage(t_msh *data);

/* Parser */
char	*check_quots(t_msh *msh);

char	**divide_cmd_args(char *input, int limit);

/* Matrix utils*/
char	**add_part(char *str, char **mtx);
void	*free_parts(char *part, char **args);
int		matrix_length(char **mtx);

/* Quot utils */
int		is_quot(char *input, int index);

/* Utils */
int		is_space(char ch);
char	*string_add(char *str, char ch);

/* Parser */
void	*parse(t_msh *msh);
void	*create_commands(t_msh *msh);

void	*add_infile(t_file_type type, char *name, t_cmd *cmd);
void	*add_outfile(t_file_type type, char *name, t_cmd *cmd);
char	**add_command(int start, int end, t_msh *msh, char **res);
void	*check_command(int *index, t_cmd *cmd, t_msh *msh);
void	*check_argument(int *index, t_cmd *cmd, t_msh *msh);
void	*check_infile(int start, int *index, t_cmd *cmd, t_msh *msh);
void	*check_outfile(int start, int *index, t_cmd *cmd, t_msh *msh);

/* Errores */
void	*set_error(t_error error, t_msh *msh);
void	check_error(t_msh *msh);
int		is_error(t_msh *msh);
void	exit_malloc(void);
void	exit_fork_pipe(t_error error);
void	exit_execve(t_msh *msh, t_cmd *cmds);

/* Expand */
# define FIRST_LETTER 1
# define MID_LETTER 2

char	*expand(t_msh *data);
char	*last_state(t_msh *data, int *i);
void	*expand_var(t_msh *msh, int *i, int aux);

/* build ins*/
void	built_ins(t_msh *msh, int nb_comand);
int		is_builtin(char *cmds);
/* export */
void	bd_export(t_msh *msh, int nb_comand);
void	export_alone(t_msh *msh);
t_bool	check_if_variable_ok(char *arguments);
char	**replace_content(t_msh *msh, char *variable, char *content);
t_bool	check_if_var_exist(t_msh *msh, char *variable);
char	*get_variable(char *arguments);
char	*get_content(char *arguments);
/* */
void	bd_env(t_msh *msh);
void	bd_echo(t_msh *msh, int nb_comand);
void	*bd_pwd(t_msh *msh);
void	bd_cd(t_msh *msh, int nb_comand);
void	bd_exit(t_msh *msh, int nb_comand);
void	bd_unset(t_msh *msh, int nb_comand);

/* variables utils */
int		ft_correct_var_char(char c, int flag);
void	*free_expand(char *str1, char *str2);

/* executor */
int		executor(t_msh *msh);
int		open_infile(t_io_file *infiles, int count, int pipe);
int		open_outfile(t_io_file *outfiles, int count, int pipe);
char	*here_doc(char *del);
void    exe_built_ins(t_msh *msh);
void	exe_one_cmd(t_msh *msh);

/* Path */
char	*get_path(t_cmd *cmds, char **envp);
/* childs */
void	first_child(t_msh *msh, int *fd, t_cmd *cmds);
void	mid_child(t_msh *msh, int *fd, int *new, t_cmd *cmds);
void	last_child(t_msh *msh, int *fd, t_cmd *cmds);


/* signals */
void	signals_manage(t_msh *msh);
void	ctrl_c_disable(void);
void	signals_here_doc();

/* Envp utils */
char	**mod_envp_shlvl(char **envp);
int		search_envp(char **envp, char *var);
char	**insert_envp(char **envp, char *var);
void	change_envp(char **envp, char *search, char *data);

#endif