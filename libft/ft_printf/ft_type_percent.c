/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 16:14:15 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:17:13 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	ft_flag_less_percent(char c, t_flags *check_flags)
{
	int	size;
	int	nb;

	size = 0;
	size += write(1, &c, 1);
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

static int	ft_width_percent(char c, t_flags *check_flags)
{
	int	size;
	int	len;

	size = 0;
	len = check_flags->fmw - 1;
	while (len > 0)
	{
		size += write(1, " ", 1);
		len -= 1;
	}
	size += write(1, &c, 1);
	check_flags->fmw = 0;
	return (size);
}

static int	ft_flag_zero_percent(char c, t_flags *check_flags)
{
	int	size;
	int	len;

	size = 0;
	len = check_flags->fmw - 1;
	while (len > 0)
	{
		size += write(1, "0", 1);
		len -= 1;
	}
	size += write(1, &c, 1);
	check_flags->fmw = 0;
	check_flags->zero = 0;
	return (size);
}

int	ft_check_percent(char c, t_flags *check_flags)
{
	int	size;

	size = 0;
	if (check_flags->less)
		return (ft_flag_less_percent(c, check_flags));
	if (check_flags->zero)
		return (ft_flag_zero_percent(c, check_flags));
	if (check_flags->fmw)
		return (ft_width_percent(c, check_flags));
	size += write(1, &c, 1);
	return (size);
}
