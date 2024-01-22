/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 22:28:34 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:22:18 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *text, const char *word, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!word[0])
		return ((char *)text);
	while (text[i] && i < len)
	{
		if (text[i] == word[0])
		{
			j = 0;
			while (word[j] == text[i + j] && (i + j) < len)
			{
				if (word[j + 1] == '\0')
					return ((char *)&text[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
