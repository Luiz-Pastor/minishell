/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 19:08:03 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:22:21 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_string(char const *s1, char const *set, size_t j)
{
	size_t	i;
	char	*str;
	size_t	count;

	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	while (ft_strchr(set, s1[j]) && s1[i] > 0)
		j--;
	count = j - i + 1;
	if (j < i)
	{
		str = (char *)ft_calloc(1, sizeof(char));
		if (str == NULL)
			return (NULL);
		return (str);
	}
	str = ft_substr(s1, i, count);
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	j;

	j = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
	{
		str = ft_calloc(1, sizeof(char));
		if (str == NULL)
			return (NULL);
		return (str);
	}
	str = ft_string(s1, set, j);
	return (str);
}
