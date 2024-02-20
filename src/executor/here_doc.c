#include "../../inc/minishell.h"

static char	*check_ava_name(char *del)
{
	char	*checker[2];
	char	*try_text;
	int		try;
	char	*res;

	try = 1;
	while(1)
	{
		try_text = ft_itoa(try);
		if (!try_text)
			return (NULL);
		checker[0] = ft_strjoin(TEMP_FOLDER, del);
		if (!checker[0])
			return (ft_mfree(1, &try_text));
		checker[1] = ft_strjoin(checker[0], try_text);
		ft_mfree(2, &try_text, &checker[0]);
		if (!checker[1])
			return (ft_mfree(1, &checker[0]));
		if (access(checker[1], F_OK) == -1)
		{
			res = checker[1];
			break ;
		}
		free(checker[1]);
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
