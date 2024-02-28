#include "../../inc/minishell.h"

static char	*getfullpath(char *del, int try)
{
	char	*main_path;
	char	*full_path;
	char	*try_text;

	try_text = ft_itoa(try);
	if (!try_text)
		exit_malloc();
	main_path = ft_strjoin(TEMP_FOLDER, del);
	if (!main_path)
		exit_malloc();
	full_path = ft_strjoin(main_path, try_text);
	ft_mfree(2, &try_text, &main_path);
	if (!full_path)
		exit_malloc();
	return (full_path);
}

static char	*check_ava_name(char *del)
{
	char	*checker;
	int		try;
	char	*res;

	try = 1;
	while (1)
	{
		checker = getfullpath(del, try);
		if (access(checker, F_OK) == -1)
		{
			res = checker;
			break ;
		}
		free(checker);
		try++;
	}
	return (res);
}

static int	get_data(int fd, char *del)
{
	char	*full_del;
	char	*buffer;

	full_del = ft_strjoin(del, "\n");
	if (!full_del)
		return (0);
	buffer = get_next_line(0);
	while (buffer && ft_strcmp(buffer, full_del))
	{
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(0);
	}
	if (buffer)
		free(buffer);
	return (1);
}

char	*here_doc(char *del)
{
	int		fd;
	char	*name;

	name = check_ava_name(del);
	if (!name)
		return (NULL);
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
	{
		free(name);
		return (NULL);
	}
	if (!get_data(fd, del))
	{
		free(name);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (name);
}
