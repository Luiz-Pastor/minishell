/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:25:10 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:26:41 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_initialize_struct(t_flags *check_flags)
{
	check_flags->plus = 0;
	check_flags->less = 0;
	check_flags->space = 0;
	check_flags->pad = 0;
	check_flags->point = 0;
	check_flags->zero = 0;
	check_flags->fmw = 0;
	check_flags->pre = 0;
	check_flags->sign = '+';
	check_flags->byte = 0;
}

static int	ft_bonus_flags(char flag, t_flags *check_flags)
{
	if (flag <= '9' && flag >= '0')
	{
		if (flag == '0' && check_flags->fmw == 0 && check_flags->pre == 0
			&& check_flags->point == 0)
			check_flags->zero = 1;
		if (check_flags->point == 0)
			check_flags->fmw = (check_flags->fmw * 10) + (int)flag - '0';
		if (check_flags->point == 1)
			check_flags->pre = (check_flags->pre * 10) + (int)flag - '0';
	}
	if (flag == '.')
		check_flags->point = 1;
	if (flag == '+')
		check_flags->plus = 1;
	if (flag == '-')
		check_flags->less = 1;
	if (flag == ' ')
		check_flags->space = 1;
	if (flag == '#')
		check_flags->pad = 1;
	return (0);
}

static int	ft_find_type(char flag, va_list args, t_flags *check_flags)
{
	check_flags->type = flag;
	if (flag == 'c')
		return (ft_check_char(va_arg(args, int), check_flags));
	if (flag == 's')
		return (ft_check_string(va_arg(args, char *), check_flags));
	if (flag == 'p')
		return (ft_check_ptr(va_arg(args, unsigned long), check_flags));
	if (flag == 'd' || flag == 'i')
		return (ft_check_nbr(va_arg(args, int), check_flags));
	if (flag == 'u')
		return (ft_check_un_nbr(va_arg(args, unsigned int), check_flags));
	if (flag == 'x')
		return (ft_check_hex(va_arg(args, unsigned int), "0123456789abcdef",
				check_flags));
	if (flag == 'X')
		return (ft_check_hex(va_arg(args, unsigned int), "0123456789ABCDEF",
				check_flags));
	if (flag == '%')
		return (ft_check_percent('%', check_flags));
	return (0);
}

static char	*ft_strchr_printf(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == '\0' && (unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		size;
	t_flags	check_flags;

	ft_initialize_struct(&check_flags);
	va_start(args, str);
	size = 0;
	while (*str != '\0')
	{
		if (*str == '%')
		{
			str++;
			while (ft_strchr_printf("+- #.0123456789", *str))
			{
				ft_bonus_flags(*str, &check_flags);
				str++;
			}
			size += ft_find_type(*str, args, &check_flags);
		}
		else
			size += write(1, str, 1);
		str++;
	}
	va_end(args);
	return (size);
}
