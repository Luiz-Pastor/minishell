/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_un_nbr2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:38:31 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:17:28 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_flag_less_un_nbr(unsigned long nb, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_zero;

	print_zero = check_flags->fmw - ft_count_nbr_unsigned(nb);
	i = 0;
	size = 0;
	size += ft_putnbr_unsigned(nb, 0);
	while (i < print_zero)
	{
		size += write(1, " ", 1);
		i++;
	}
	check_flags->less = 0;
	check_flags->fmw = 0;
	return (size);
}

int	ft_flag_zero_un_nbr(unsigned long nb, t_flags *check_flags)
{
	unsigned int	size;
	unsigned int	p_zero;

	if (check_flags->fmw > ft_count_nbr_unsigned(nb))
		p_zero = check_flags->fmw - ft_count_nbr_unsigned(nb);
	else
		p_zero = 0;
	size = 0;
	while (p_zero > 0)
	{
		size += write(1, "0", 1);
		p_zero -= 1;
	}
	size += ft_putnbr_unsigned(nb, 0);
	check_flags->zero = 0;
	check_flags->fmw = 0;
	return (size);
}

int	ft_width_un_nbr(unsigned long nb, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_space;

	size = 0;
	print_space = check_flags->fmw - ft_count_nbr_unsigned(nb);
	i = 0;
	while (i++ < print_space)
		size += write(1, " ", 1);
	size += ft_putnbr_unsigned(nb, 0);
	ft_initialize_struct(check_flags);
	return (size);
}
