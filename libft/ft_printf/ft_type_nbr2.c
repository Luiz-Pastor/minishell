/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_nbr2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 12:11:52 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:17:06 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_flag_plus_nbr(t_flags *check_flags)
{
	int	size;

	size = 0;
	size += ft_check_sign(check_flags);
	check_flags->plus = 0;
	check_flags->sign = '+';
	return (size);
}

int	ft_flag_space_nbr(t_flags *check_flags)
{
	int	size;

	size = 0;
	size += ft_check_sign(check_flags);
	check_flags->space = 0;
	check_flags->sign = '+';
	return (size);
}

int	ft_flag_zero_nbr(long nb, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_zero;

	size = 0;
	size += ft_check_sign(check_flags);
	if (nb == 0 && check_flags->fmw == 0 && check_flags->pre == 0
		&& check_flags->point == 1)
	{
		ft_initialize_struct(check_flags);
		return (size);
	}
	print_zero = check_flags->fmw - (ft_count_nbr(nb, 0) + check_flags->byte);
	if (check_flags->point == 1)
		print_zero = check_flags->fmw - ft_count_nbr(nb, 0);
	i = 0;
	while (i++ < print_zero)
		size += write(1, "0", 1);
	size += ft_putnbr_printf(nb, 0, check_flags);
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_flag_less_nbr(long nb, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_space;

	size = 0;
	size += ft_check_sign(check_flags);
	print_space = check_flags->fmw - (ft_count_nbr(nb, 0) + check_flags->byte);
	i = 0;
	if (nb == 0 && check_flags->point == 1 && check_flags->pre == 0
		&& check_flags->fmw <= ft_count_nbr(nb, 0))
		return (size);
	else if (nb == 0 && check_flags->point == 1 && check_flags->pre == 0)
		size += write(1, " ", 1);
	else
		size += ft_putnbr_printf(nb, 0, check_flags);
	while (i < print_space)
	{
		size += write(1, " ", 1);
		i++;
	}
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_flag_point_nbr(long nb, t_flags *check_flags)
{
	if (check_flags->fmw == 0 || (check_flags->zero == 1
			&& check_flags->fmw < check_flags->pre))
		return (ft_case_one_pre_nbr(nb, check_flags));
	else if (check_flags->pre == 0)
		return (ft_case_two_pre_nbr(nb, check_flags));
	else if (check_flags->pre < check_flags->fmw && check_flags->less == 0)
		return (ft_case_three_pre_nbr(nb, check_flags));
	else if (check_flags->pre < check_flags->fmw && check_flags->less == 1)
		return (ft_case_three2_pre_nbr(nb, check_flags));
	else if (check_flags->pre >= check_flags->fmw)
		return (ft_case_four_pre_nbr(nb, check_flags));
	return (0);
}
