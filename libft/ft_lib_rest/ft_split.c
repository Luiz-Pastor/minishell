/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:51:23 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:21:52 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (ft_strlen(s) < 1)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != '\0' && s[i] != c)
		{
			nb++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		while (s[i] != '\0' && s[i] == c)
			i++;
	}
	return (nb);
}

void	*ft_free_split(char **memory)
{
	int	i;

	i = 0;
	while (memory[i] != NULL)
	{
		free(memory[i]);
		i++;
	}
	free(memory);
	return (NULL);
}

static char	**ft_string(int nb, char const *s, char c, char **result)
{
	int	i;
	int	x;
	int	start;

	i = 0;
	x = 0;
	while (x < nb && s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		result[x] = ft_substr(s, start, i - start);
		if (result[x] == NULL)
			return (ft_free_split(result));
		x++;
	}
	result[x] = NULL;
	return (result);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		nb;

	nb = ft_countwords(s, c);
	result = (char **)malloc((nb + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = ft_string(nb, s, c, result);
	return (result);
}
