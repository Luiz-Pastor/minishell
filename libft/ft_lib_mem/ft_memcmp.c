/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:53:51 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:21:14 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *buffer1, const void *buffer2, size_t count)
{
	size_t				i;
	const unsigned char	*buff1;
	const unsigned char	*buff2;

	buff1 = (const unsigned char *)buffer1;
	buff2 = (const unsigned char *)buffer2;
	i = 0;
	while (i < count)
	{
		if (buff1[i] != buff2[i])
			return (buff1[i] - buff2[i]);
		i++;
	}
	return (0);
}
