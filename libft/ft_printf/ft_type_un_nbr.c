/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_un_nbr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 13:41:26 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:17:24 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_count_nbr_unsigned(unsigned long nb)
{
	unsigned long	len;

	len = 0;
	while (nb >= 10)
	{
		len += 1;
		nb = nb / 10;
	}
	len += 1;
	return (len);
}

int	ft_putnbr_unsigned(unsigned long nb, unsigned int size)
{
	if (nb >= 10)
		size = ft_putnbr_unsigned((nb / 10), size);
	size += write(1, &(char){(nb % 10) + '0'}, 1);
	return (size);
}

int	ft_flag_point_un_nbr(unsigned long nb, t_flags *check_flags)
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

int	ft_check_un_nbr(unsigned int n, t_flags *check_flags)
{
	unsigned long	nb;

	nb = (unsigned long)n;
	if (check_flags->point == 1)
		return (ft_flag_point_un_nbr(nb, check_flags));
	if (check_flags->zero == 1)
		return (ft_flag_zero_un_nbr(nb, check_flags));
	if (check_flags->less == 1)
		return (ft_flag_less_un_nbr(nb, check_flags));
	if (check_flags->fmw != 0)
		return (ft_width_un_nbr(nb, check_flags));
	return (ft_putnbr_unsigned(nb, 0));
}
