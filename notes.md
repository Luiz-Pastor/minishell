# FUNCIONES
## Useful functions
```
- printf
- malloc
- free
- exit
- perror

```

## File functions
```
- open
- close
- read
- write
- unlink
- access
```

## Process functions
```
- fork
- pipe
- wait
- waitpid
- dup
- dup2
- execve
```
<br><br>
# New functions
```
[X] readline
[X] rl_clear_history
[X] rl_on_new_line
[X] rl_replace_line
[X] rl_redisplay
[X] add_history
[X] wait3
[X] wait4
[X] getcwd
[X] chdir
[X] stat
[X] lstat
[X] fstat
[X] opendir
[X] readdir
[X] closedir
[X] strerror
[X] isatty
[X] ttyname
[X] ttyslot
[] ioctl
[] getenv
[] tcsetattr
[] tcgetattr
[] tgetent
[] tgetflag
[] tgetnum
[] tgetstr
[] tgoto
[] tputs
[] signal
[] sigaction
[] kill
```

```c
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
 * brief	It will read a line from the terminal and return it, using prompt as a prompt
 *
 * param	prompt: Prompt that will be displayed on the terminal
 *
 * return	The line readed
*/
char *readline (const char *prompt);
```

```c
/*
 *
 * brief	Clear the history list by deleting all of the entries
 *
*/
void rl_clear_history (void);
```

```c
/*
 *
 * brief	Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline.
 *
*/
int rl_on_new_line (void);
```

```c
/*
 *
 * brief	Replace the contents of `rl_line_buffer` with text. The point and mark are preserved, if possible. If `clear_undo` is non-zero, the undo list associated with the current line is cleared.
 *
*/
void rl_replace_line (const char *text, int clear_undo);
```

```c
/*
 *
 * brief	Change what’s displayed on the screen to reflect the current contents of `rl_line_buffer`.
 *
*/
void rl_redisplay (void);
```

```c
/*
 *
 * brief	Place string at the end of the history list. The associated data field (if any) is set to NULL.
 *
*/
void add_history (const char *string);
```

```c
/*
 *  wait3(status, options, rusage) = waitpid(-1, status, options)
*/
pid_t wait3(int *status, int options, struct rusage *rusage);
```

```c
/*
 *	wait4(pid, status, options, rusage) = waitpid(pid, status, options)
*/
pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);
```

```c
/*
 *
 * brief	Determines the path name of the working directory and stores it in buffer.
 *
 * param	size: The number of characters in the buffer area.
 * param	buffer: The name of the buffer that will be used to hold the path name of the working directory
 *
 * return	a pointer to `buffer`, or NULL (error and errno)
*/
char *getcwd(char *buffer, size_t size);
```

```c
/*
 *
 * brief	The chdir command is a system function (system call) that is used to change the current working directory
 *
 * param	path: The directory path that the user want to make the current working directory
 *
 * return	0 on success, -1 on error (errno)
*/
int chdir(const char *path);
```

```c
/*
 *
 * brief	It obtains information about the named file and write it to the area pointed to by the `buf` argument
 * 
 * param	path: Path of the file
 * param	buf: Pointer to the struct where the info will be saved
 * 
 * return	0 on success, -1 on error (errno)
 *
*/
int stat(const char *restrict path, struct stat *restrict buf);
```

```c
/*
 * Like `stat` but it saves the information about a symbolic link
 *
*/
int lstat(const char *restrict path, struct stat *restrict buf);
```

```c
/*
 * Like `stat` but it saves the information about a open file, with a file descriptor
 *
*/
int fstat(int fildes, struct stat *buf);
```

```c
/*
 *
 * brief	Open a directory stream corresponding to the directory named by the dirname argument
 *
 * param	dirname: Directory name/path
 * 
 * return	A pointer to a `DIR` type, or NULLon error (errno)
*/
DIR *opendir(const char *dirname);
```

```c
/*
 *
 * brief	Returns a pointer to a structure representing the directory entry at the current position in the directory stream
 *
 * param	dirp: The path of the directory
 * 
 * return	A pointer to a struct, or NULL in case of error
*/
struct dirent *readdir(DIR *dirp);
```

```c
/*
 *
 * brief	Close the directory stream referred to by the argument dirp
 * 
 * param	dirp: The struct with the folder information
 * 
 * return	0 on success, -1 on error (errno)
*/
int closedir(DIR *dirp);
```

```c
/*
 *
 * brief	Gets a system error message string
 * 
 * param	errnum: Error number
 * 
 * return	A pointer to an error-message string
 *
*/
char * strerror(int errnum );
```

```c
/*
 *
 * brief	Function tests whether `fd` is an open file descriptor referring to a terminal.
 * 
 * param	fd: A valid file descriptor
 * 
 * return	1 if `fd` is a file descriptor referring to a terminal, 0 on other case (errno)
 *
*/
int isatty(int fd);
```

```c
/*
 *
 * brief	Returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd
 *
 * param	fd: the file descriptor
 * 
 * return	A pointer to the pathname of the file
*/
char *ttyname(int fd);
```

```c
/*
 *
 * brief	Returns the index of the current user's entry in some file
 * 
*/
 int ttyslot(void);
```