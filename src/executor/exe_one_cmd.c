#include "../../inc/minishell.h"

char    *here_doc(char *uwu)
{
    uwu = NULL;
    return (uwu);
}
static int  open_infile(t_io_file *infiles, int count)
{
    int i;
    int fd;
    char *name;

    i = 0;
    if (count == 0)
        return (STDIN_FILENO);
    while(i < count)
    {
        if (infiles[i].type == INFILE)
        {
            fd = open(infiles[i].name, O_RDONLY);
            if (fd < 0)
                perror(infiles[i].name);
        }
        else
        {
            name = here_doc(infiles[i].name);
            if (!name)
                perror(infiles[i].name);
            fd = open(name, O_RDONLY);
            if (fd < 0)
                perror(name);
        }
        if (i != count - 1)
            close(fd);
        i++;
    }
    return (fd);
        
}

static int open_outfile(t_io_file *outfiles, int count)
{
    int i;
    int fd;

    i = 0;
    if (count == 0)
        return (STDOUT_FILENO);
    while(i < count)
    {
        if (outfiles[i].type == TRUNC)
            fd = open(outfiles[i].name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
        else
            fd = open(outfiles[i].name, O_WRONLY | O_CREAT | O_APPEND, 0777);
        if (fd < 0)
            perror(outfiles[i].name);
        if (i != count - 1)
            close(fd);
        i++;
    }
    return (fd);
}

void    exe_built_ins(t_msh *msh)
{
    int fd_in;
    int fd_out;

    fd_in = open_infile(msh->cmds[0].infiles, msh->cmds[0].infiles_count);
    if (fd_in < 0)
        return ;
    fd_out = open_outfile(msh->cmds[0].outfiles, msh->cmds[0].outfiles_count);
    if (fd_out < 0)
        return ;
    dup2(fd_in, STDIN_FILENO);
    dup2(fd_out, STDOUT_FILENO);
    built_ins(msh, 0);
    dup2(STDIN_FILENO, fd_in);
    dup2(STDOUT_FILENO, fd_out);
}
