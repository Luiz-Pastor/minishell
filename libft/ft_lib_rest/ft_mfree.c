/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 11:13:20 by lpastor-          #+#    #+#             */
/*   Updated: 2024/01/23 11:23:56 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_mfree(int count, ...)
{
	va_list	args;
	int		index;
	void	**pointer;

	index = 0;
	va_start(args, count);
	while (index < count)
	{
		pointer = va_arg(args, void **);
		free(*pointer);
		*pointer = NULL;
	}
	va_end(args);
	return (NULL);
}
