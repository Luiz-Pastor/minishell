/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:19:07 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:17:21 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_putstr_printf(char *str, int nb)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (nb > 0 && str[i] != '\0')
	{
		size += write(1, &str[i], 1);
		i++;
		nb -= 1;
	}
	return (size);
}

static int	ft_flag_less_string(char *str, t_flags *check_flags)
{
	int	size;
	int	nb;

	size = 0;
	size += ft_putstr_printf(str, ft_strlen_printf(str));
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

static int	ft_point(char *str, t_flags *check_flags)
{
	int	size;
	int	nb;

	nb = 0;
	size = 0;
	if (str[0] == '\0')
		nb = check_flags->fmw;
	else if (check_flags->fmw >= check_flags->pre)
	{
		if (check_flags->pre > ft_strlen_printf(str))
			nb = check_flags->fmw - ft_strlen_printf(str);
		if (check_flags->pre <= ft_strlen_printf(str))
			nb = check_flags->fmw - check_flags->pre;
	}
	else if (check_flags->fmw < check_flags->pre)
		nb = check_flags->fmw - ft_strlen_printf(str);
	while (nb > 0)
	{
		size += write(1, " ", 1);
		nb -= 1;
	}
	size += ft_putstr_printf(str, check_flags->pre);
	return (size);
}

static int	ft_flag_point_string(char *str, t_flags *check_flags)
{
	int	size;
	int	nb;

	size = 0;
	if (check_flags->less == 1)
	{
		size += ft_putstr_printf(str, check_flags->pre);
		nb = check_flags->fmw - size;
		while (nb > 0)
		{
			size += write(1, " ", 1);
			nb -= 1;
		}
		check_flags->less = 0;
	}
	else
		size += (ft_point(str, check_flags));
	check_flags->pre = 0;
	check_flags->fmw = 0;
	check_flags->point = 0;
	return (size);
}

int	ft_check_string(char *str, t_flags *check_flags)
{
	char	*aux;

	if (str == NULL)
		aux = "(null)";
	else
		aux = str;
	if (check_flags->point == 1)
		return (ft_flag_point_string(aux, check_flags));
	if (check_flags->less == 1)
		return (ft_flag_less_string(aux, check_flags));
	if (check_flags->fmw != 0)
		return (ft_width_str(aux, check_flags));
	return (ft_putstr_printf(aux, ft_strlen_printf(aux)));
}
