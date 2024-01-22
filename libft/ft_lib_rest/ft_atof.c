/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:44:14 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:21:43 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static double	ft_atof2(char *str, double nb)
{
	double	dec;
	double	aux;

	dec = 10;
	while (*str >= '0' && *str <= '9')
	{
		nb = ((*str - '0') + (nb * 10));
		str++;
	}
	if (*str == '.')
	{
		dec = 10;
		str++;
		while (*str >= '0' && *str <= '9')
		{
			aux = ((*str - '0'));
			nb = nb + (aux / dec);
			dec *= 10;
			str++;
		}
	}
	return (nb);
}

double	ft_atof(char *str)
{
	double	nb;
	int		sign;

	nb = 0;
	sign = 0;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = 1;
		str++;
	}
	nb = ft_atof2(str, nb);
	if (sign == 1)
		nb = nb * -1;
	return (nb);
}
