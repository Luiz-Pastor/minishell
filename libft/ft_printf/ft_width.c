/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 18:24:32 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:17:31 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_strlen_printf(const char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_width_str(char *str, t_flags *check_flags)
{
	int	size;
	int	len;

	size = 0;
	if (str[0] == '\0')
		len = check_flags->fmw;
	else
		len = check_flags->fmw - ft_strlen_printf(str);
	while (len > 0)
	{
		size += write(1, " ", 1);
		len -= 1;
	}
	size += ft_putstr_printf(str, ft_strlen_printf(str));
	check_flags->fmw = 0;
	return (size);
}

int	ft_width_nbr(long nb, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_space;

	size = 0;
	ft_count_sign(check_flags);
	print_space = check_flags->fmw - (ft_count_nbr(nb, 0) + check_flags->byte);
	i = 0;
	while (i++ < print_space)
		size += write(1, " ", 1);
	size += ft_check_sign(check_flags);
	size += ft_putnbr_printf(nb, 0, check_flags);
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_prewidth_nbr(long nb, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_space;

	size = 0;
	ft_count_sign(check_flags);
	print_space = check_flags->fmw - (ft_count_nbr(nb, 0) + check_flags->byte);
	i = 0;
	while (i++ < print_space)
		size += write(1, " ", 1);
	if (nb == 0 && check_flags->point == 1 && check_flags->pre == 0
		&& check_flags->fmw >= (ft_count_nbr(nb, 0) + check_flags->byte))
	{
		size += write(1, " ", 1);
		size += ft_check_sign(check_flags);
		return (size);
	}
	if (nb == 0 && check_flags->plus == 1)
		return (size += ft_check_sign(check_flags));
	size += ft_check_sign(check_flags);
	size += ft_putnbr_printf(nb, 0, check_flags);
	ft_initialize_struct(check_flags);
	return (size);
}

int	ft_prewidth_hex(unsigned long nb, char *base, t_flags *check_flags)
{
	int	size;
	int	i;
	int	print_space;
	int	len;

	len = ft_count_putnbr_hex(nb, "0123456789abcdef", 0) + check_flags->byte;
	size = 0;
	if (nb > 0)
		ft_count_sign(check_flags);
	print_space = check_flags->fmw - (len + check_flags->byte);
	i = 0;
	while (i++ < print_space)
		size += write(1, " ", 1);
	if (nb == 0 && check_flags->point == 1 && check_flags->pre == 0
		&& check_flags->fmw >= len)
	{
		size += write(1, " ", 1);
		ft_initialize_struct(check_flags);
		return (size);
	}
	if (nb > 0)
		size += ft_check_sign(check_flags);
	size += ft_putnbr_hex(nb, base, 0);
	ft_initialize_struct(check_flags);
	return (size);
}
