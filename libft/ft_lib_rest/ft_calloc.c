/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:12:07 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:21:48 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	void	*buffer;

	if (number == SIZE_MAX || size == SIZE_MAX)
		return (NULL);
	buffer = malloc(number * size);
	if (buffer == NULL)
		return (0);
	ft_bzero(buffer, number * size);
	return (buffer);
}
