/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_nbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:36:47 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:17:01 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_count_nbr(long n, int len)
{
	if (n <= -10 || n >= 10)
		len = ft_count_nbr((n / 10), len);
	len += 1;
	return (len);
}

int	ft_putnbr_printf(long nb, int size, t_flags *check_flags)
{
	char	c;

	if (size == 0 && check_flags->sign == '-' && check_flags->point == 0
		&& check_flags->zero == 0 && check_flags->plus == 0
		&& check_flags->fmw == 0 && check_flags->less == 0
		&& check_flags->space == 0)
		size += ft_check_sign(check_flags);
	if (nb <= -10 || nb >= 10)
		size = ft_putnbr_printf((nb / 10), size, check_flags);
	c = (nb % 10) + '0';
	size += write(1, &c, 1);
	return (size);
}

int	ft_check_sign(t_flags *check_flags)
{
	int	size;

	size = 0;
	if (check_flags->pad == 1)
	{
		if (check_flags->type == 'x')
			size += write(1, "0x", 2);
		else
			size += write(1, "0X", 2);
		check_flags->byte = size;
	}
	if (check_flags->type == 'x' || check_flags->type == 'X')
		return (size);
	if (check_flags->space == 1 && check_flags->sign == '-')
		size += write(1, &check_flags->sign, 1);
	else if (check_flags->space == 1 && check_flags->sign == '+')
		size += write(1, " ", 1);
	else if (check_flags->plus == 1 && check_flags->sign == '+')
		size += write(1, &check_flags->sign, 1);
	else if (check_flags->sign == '-')
		size += write(1, &check_flags->sign, 1);
	check_flags->byte = size;
	return (size);
}

void	ft_count_sign(t_flags *check_flags)
{
	if (check_flags->pad == 1)
		check_flags->byte = 2;
	else if (check_flags->space == 1 && check_flags->sign == '-')
		check_flags->byte = 1;
	else if (check_flags->space == 1 && check_flags->sign == '+')
		check_flags->byte = 1;
	else if (check_flags->plus == 1 && check_flags->sign == '+')
		check_flags->byte = 1;
	else if (check_flags->sign == '-')
		check_flags->byte = 1;
}

int	ft_check_nbr(int n, t_flags *check_flags)
{
	long	nb;
	int		size;

	size = 0;
	nb = (long)n;
	if (nb < 0)
	{
		check_flags->sign = '-';
		nb *= -1;
	}
	if (check_flags->point == 1)
		return (ft_flag_point_nbr(nb, check_flags));
	if (check_flags->zero == 1)
		return (ft_flag_zero_nbr(nb, check_flags));
	if (check_flags->less == 1)
		return (ft_flag_less_nbr(nb, check_flags));
	if (check_flags->fmw != 0)
		return (ft_width_nbr(nb, check_flags));
	if (check_flags->plus == 1)
		size += ft_flag_plus_nbr(check_flags);
	if (check_flags->space == 1)
		size += ft_flag_space_nbr(check_flags);
	size += ft_putnbr_printf(nb, 0, check_flags);
	ft_initialize_struct(check_flags);
	return (size);
}
