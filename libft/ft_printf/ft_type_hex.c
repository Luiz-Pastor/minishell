/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 15:25:05 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/22 12:24:26 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putnbr_hex(unsigned long nb, char *base, int size)
{
	if (nb < 16)
	{
		size += write(1, &base[nb], 1);
		return (size);
	}
	size = ft_putnbr_hex((nb / 16), base, size);
	size += write(1, &base[nb % 16], 1);
	return (size);
}

int	ft_flag_less_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	int	size;
	int	len;

	size = 0;
	if (nb > 0)
	{
		size += ft_check_sign(check_flags);
		size += ft_putnbr_hex(nb, base, 0);
	}
	if (check_flags->point == 0 && nb == 0)
		size += ft_putnbr_hex(nb, base, 0);
	len = check_flags->fmw - size;
	while (len > 0)
	{
		size += write(1, " ", 1);
		len -= 1;
	}
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_flag_pad_hex(unsigned long nb, t_flags *check_flags)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (ft_putnbr_hex(nb, "0123456789ABCDEF", 0));
	if (check_flags->type == 'X')
	{
		size += write(1, "0X", 2);
		size += ft_putnbr_hex(nb, "0123456789ABCDEF", 0);
	}
	if (check_flags->type == 'x')
	{
		size += write(1, "0x", 2);
		size += ft_putnbr_hex(nb, "0123456789abcdef", 0);
	}
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_flag_point_hex(unsigned long nb, t_flags *check_flags)
{
	char	*base;

	if (check_flags->type == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (check_flags->fmw == 0 || (check_flags->zero == 1
			&& check_flags->fmw < check_flags->pre))
		return (ft_case_one_pre_hex(nb, base, check_flags));
	else if (check_flags->pre == 0)
		return (ft_case_two_pre_hex(nb, base, check_flags));
	else if (check_flags->pre < check_flags->fmw && check_flags->less == 0)
		return (ft_case_three_pre_hex(nb, base, check_flags));
	else if (check_flags->pre < check_flags->fmw && check_flags->less == 1)
		return (ft_case_three2_pre_hex(nb, base, check_flags));
	else if (check_flags->pre >= check_flags->fmw)
		return (ft_case_four_pre_hex(nb, base, check_flags));
	return (0);
}

int	ft_check_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	if (check_flags->point == 1)
		return (ft_flag_point_hex(nb, check_flags));
	if (check_flags->zero == 1)
		return (ft_flag_zero_hex(nb, base, check_flags));
	if (check_flags->less == 1)
		return (ft_flag_less_hex(nb, base, check_flags));
	if (check_flags->fmw != 0)
		return (ft_width_hex(nb, check_flags));
	if (check_flags->pad == 1)
		return (ft_flag_pad_hex(nb, check_flags));
	return (ft_putnbr_hex(nb, base, 0));
}
