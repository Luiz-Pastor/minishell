/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:59:06 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:22:07 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	src_length;
	size_t	dest_length;

	src_length = ft_strlen(src);
	dest_length = ft_strlen(dest);
	i = dest_length;
	j = 0;
	if (size <= dest_length)
		return (src_length + size);
	while (src[j] != '\0' && j < (size - dest_length - 1))
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (src_length + dest_length);
}
