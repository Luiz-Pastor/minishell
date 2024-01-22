/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:17:03 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:21:12 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(void *buffer, int c, size_t count)
{
	char	*buffer1;
	size_t	i;

	i = 0;
	buffer1 = (char *)buffer;
	while (i < count)
	{
		if (buffer1[i] == (char)c)
			return ((void *)&buffer1[i]);
		i++;
	}
	return (NULL);
}
