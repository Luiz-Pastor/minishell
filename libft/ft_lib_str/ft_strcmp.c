/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 12:23:28 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:22:00 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	int	i;
	int	len;
	int	len2;

	if (str2 == NULL)
		return (1);
	len = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len < len2)
		len = len2;
	i = 0;
	while ((str1[i] != '\0' || str2[i] != '\0') && i < len)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		else
			i++;
	}
	return (0);
}
