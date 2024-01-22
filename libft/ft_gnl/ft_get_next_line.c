/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 15:33:34 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:25:56 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

void	*ft_gnl_free(char *buff, char *aux)
{
	free(aux);
	free(buff);
	buff = NULL;
	aux = NULL;
	return (NULL);
}

static char	*ft_read(int fd, char *buff)
{
	char	*aux;
	int		nb;

	nb = 1;
	aux = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!aux)
		return (ft_gnl_free(buff, NULL));
	while (nb > 0 && !ft_gnl_strchr(buff, '\n'))
	{
		nb = read(fd, aux, BUFFER_SIZE);
		if (nb == -1)
			return (ft_gnl_free(buff, aux));
		aux[nb] = '\0';
		if (aux[0] == '\0')
		{
			free(aux);
			aux = NULL;
			return (buff);
		}
		buff = ft_gnl_strjoin(buff, aux);
		if (!buff)
			return (ft_gnl_free(buff, aux));
	}
	free(aux);
	return (buff);
}

static char	*ft_getline(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
		i++;
	if (buff[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (ft_gnl_free(buff, NULL));
	i = 0;
	while (buff[i] != '\n' && buff[i] != '\0')
	{
		line[i] = buff[i];
		i++;
	}
	if (buff[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*readnotprint[FOPEN_MAX];
	char		*line;
	int			i;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	readnotprint[fd] = ft_read(fd, readnotprint[fd]);
	if (!readnotprint[fd])
		return (NULL);
	line = ft_getline(readnotprint[fd]);
	if (!line)
		return (NULL);
	i = ft_gnl_strlen(line);
	readnotprint[fd] = ft_gnl_substr(readnotprint[fd], i,
			(ft_gnl_strlen(readnotprint[fd]) - i));
	return (line);
}
