/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_hex3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 01:05:24 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:16:52 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_flag_zero_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_zero;
	int	len;

	size = 0;
	len = ft_count_putnbr_hex(nb, "0123456789abcdef", 0);
	if (check_flags->pad == 1 && check_flags->zero == 1 && nb == 0)
		check_flags->byte = 0;
	else if (nb > 0)
		size += ft_check_sign(check_flags);
	if (check_flags->point == 1)
		check_flags->byte = 0;
	print_zero = check_flags->fmw - (len + check_flags->byte);
	i = 0;
	while (i < print_zero)
	{
		size += write(1, "0", 1);
		i++;
	}
	size += ft_putnbr_hex(nb, base, 0);
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_width_hex(long nb, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_space;
	int	len;

	len = ft_count_putnbr_hex(nb, "0123456789abcdef", 0);
	size = 0;
	if (nb > 0)
		ft_count_sign(check_flags);
	print_space = check_flags->fmw - (len + check_flags->byte);
	i = 0;
	while (i++ < print_space)
		size += write(1, " ", 1);
	if (nb > 0)
		size += ft_check_sign(check_flags);
	if (check_flags->type == 'X')
		size += ft_putnbr_hex(nb, "0123456789ABCDEF", 0);
	if (check_flags->type == 'x')
		size += ft_putnbr_hex(nb, "0123456789abcdef", 0);
	ft_initialize_struct(check_flags);
	return (size);
}
