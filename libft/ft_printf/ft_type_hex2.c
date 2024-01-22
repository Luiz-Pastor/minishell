/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_hex2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 17:42:39 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:16:47 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_case_one_pre_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	int	size;

	size = 0;
	if (check_flags->pre == 0 && nb == 0)
	{
		ft_initialize_struct(check_flags);
		return (size);
	}
	check_flags->fmw = check_flags->pre;
	size += ft_flag_zero_hex(nb, base, check_flags);
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_case_two_pre_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	int	size;

	size = 0;
	if (check_flags->less == 0)
		size += ft_prewidth_hex(nb, base, check_flags);
	else
		size += ft_flag_less_hex(nb, base, check_flags);
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_case_three_pre_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	int	size;
	int	i;
	int	len;

	len = ft_count_putnbr_hex(nb, base, 0);
	size = 0;
	i = 0;
	if (nb > 0)
		ft_count_sign(check_flags);
	if (len >= check_flags->pre)
		i = check_flags->fmw - len - check_flags->byte;
	else if (len < check_flags->pre)
		i = check_flags->fmw - check_flags->pre - check_flags->byte;
	while (i-- > 0)
		size += write(1, " ", 1);
	if (nb > 0)
		size += ft_check_sign(check_flags);
	i = check_flags->pre - len;
	while (i-- > 0)
		size += write(1, "0", 1);
	size += ft_putnbr_hex(nb, base, 0);
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_case_three2_pre_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	int	size;
	int	i;
	int	len;

	len = ft_count_putnbr_hex(nb, base, 0);
	size = 0;
	if (nb > 0)
		size += ft_check_sign(check_flags);
	i = check_flags->pre - len;
	while (i-- > 0)
		size += write(1, "0", 1);
	size += ft_putnbr_hex(nb, base, 0);
	if (len >= check_flags->pre)
		i = check_flags->fmw - len - check_flags->byte;
	else if (len < check_flags->pre)
		i = check_flags->fmw - check_flags->pre - check_flags->byte;
	while (i-- > 0)
		size += write(1, " ", 1);
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_case_four_pre_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	int	size;
	int	i;
	int	len;

	len = ft_count_putnbr_hex(nb, base, 0);
	size = 0;
	if (nb > 0)
		size += ft_check_sign(check_flags);
	i = check_flags->pre - len;
	while (i-- > 0)
		size += write(1, "0", 1);
	size += ft_putnbr_hex(nb, base, 0);
	ft_initialize_struct(check_flags);
	return (size);
}
