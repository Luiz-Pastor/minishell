/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 18:31:33 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:17:17 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_count_putnbr_hex(unsigned long nb, char *base, int len)
{
	if (nb < 16)
	{
		len += 1;
		return (len);
	}
	len = ft_count_putnbr_hex((nb / 16), base, len);
	len += 1;
	return (len);
}

static int	ft_flag_less_ptr(unsigned long ptr, t_flags *check_flags)
{
	int	size;
	int	nb;

	size = 0;
	size += write(1, "0x", 2);
	size += ft_putnbr_hex(ptr, "0123456789abcdef", 0);
	nb = check_flags->fmw - size;
	while (nb > 0)
	{
		size += write(1, " ", 1);
		nb -= 1;
	}
	check_flags->less = 0;
	check_flags->fmw = 0;
	return (size);
}

static int	ft_width_ptr(unsigned long ptr, t_flags *check_flags)
{
	int	size;
	int	len;

	size = 0;
	len = check_flags->fmw - ft_count_putnbr_hex(ptr, "0123456789abcdefg", 0)
		- 2;
	while (len > 0)
	{
		size += write(1, " ", 1);
		len -= 1;
	}
	size += write(1, "0x", 2);
	size += ft_putnbr_hex(ptr, "0123456789abcdefg", 0);
	check_flags->fmw = 0;
	return (size);
}

int	ft_check_ptr(unsigned long ptr, t_flags *check_flags)
{
	int	size;

	size = 0;
	if (check_flags->less == 0 && check_flags->fmw != 0)
		return (ft_width_ptr(ptr, check_flags));
	if (check_flags->less == 1)
		return (ft_flag_less_ptr(ptr, check_flags));
	size += write(1, "0x", 2);
	size += ft_putnbr_hex(ptr, "0123456789abcdef", 0);
	return (size);
}
