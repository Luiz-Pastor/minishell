/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:54:29 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/22 13:03:02 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(void *str, size_t n)
{
	char	*dest;
	size_t	i;

	dest = (char *)str;
	i = 0;
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
}
