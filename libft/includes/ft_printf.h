/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 19:25:31 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 13:22:08 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "default_libs.h"

typedef struct s_flags
{
	int		plus;
	int		space;
	int		less;
	int		point;
	int		zero;
	int		pad;
	char	type;
	int		fmw;
	int		pre;
	char	sign;
	int		byte;
}			t_flags;

//main ok
int			ft_printf(char const *str, ...) __attribute__((format(printf, 1,
						2)));
void		ft_initialize_struct(t_flags *check_flags);

//char ok
int			ft_check_char(int c, t_flags *check_flags);

//string
int			ft_check_string(char *str, t_flags *check_flags);
int			ft_putstr_printf(char *str, int nb);

//ptr
int			ft_check_ptr(unsigned long ptr, t_flags *check_flags);

//nbr ok
int			ft_check_nbr(int nb, t_flags *check_flags);
int			ft_putnbr_printf(long n, int size, t_flags *check_flags);
int			ft_count_nbr(long n, int len);
int			ft_check_sign(t_flags *check_flags);
void		ft_count_sign(t_flags *check_flags);

//nbr2
int			ft_flag_zero_nbr(long nb, t_flags *check_flags);
int			ft_flag_space_nbr(t_flags *check_flags);
int			ft_flag_plus_nbr(t_flags *check_flags);
int			ft_flag_point_nbr(long nb, t_flags *check_flags);
int			ft_flag_less_nbr(long nb, t_flags *check_flags);

//nbr3 ok
int			ft_case_one_pre_nbr(long nb, t_flags *check_flags);
int			ft_case_two_pre_nbr(long nb, t_flags *check_flags);
int			ft_case_three_pre_nbr(long nb, t_flags *check_flags);
int			ft_case_three2_pre_nbr(long nb, t_flags *check_flags);
int			ft_case_four_pre_nbr(long nb, t_flags *check_flags);

//nbr un
int			ft_flag_point_un_nbr(unsigned long nb, t_flags *check_flags);
int			ft_check_un_nbr(unsigned int nb, t_flags *check_flags);
int			ft_putnbr_unsigned(unsigned long nb, unsigned int size);
int			ft_count_nbr_unsigned(unsigned long nb);

//nbr2 un
int			ft_flag_less_un_nbr(unsigned long nb, t_flags *check_flags);
int			ft_flag_zero_un_nbr(unsigned long nb, t_flags *check_flags);
int			ft_width_un_nbr(unsigned long nb, t_flags *check_flags);

//width
int			ft_strlen_printf(const char *str);
int			ft_width_str(char *str, t_flags *check_flags);
int			ft_width_nbr(long nb, t_flags *check_flags);
int			ft_prewidth_nbr(long nb, t_flags *check_flags);
int			ft_prewidth_hex(unsigned long nb, char *base, t_flags *check_flags);

//hex
int			ft_putnbr_hex(unsigned long nb, char *base, int size);
int			ft_count_putnbr_hex(unsigned long nb, char *base, int len);
int			ft_flag_point_hex(unsigned long n, t_flags *check_flags);
int			ft_check_hex(unsigned long nb, char *base, t_flags *check_flags);
int			ft_flag_zero_hex(unsigned long nb, char *base,
				t_flags *check_flags);
int			ft_flag_less_hex(unsigned long nb, char *base,
				t_flags *check_flags);
int			ft_width_hex(long nb, t_flags *check_flags);

//hex2
int			ft_case_one_pre_hex(unsigned long nb, char *base,
				t_flags *check_flags);
int			ft_case_two_pre_hex(unsigned long nb, char *base,
				t_flags *check_flags);
int			ft_case_three_pre_hex(unsigned long nb, char *base,
				t_flags *check_flags);
int			ft_case_three2_pre_hex(unsigned long nb, char *base,
				t_flags *check_flags);
int			ft_case_four_pre_hex(unsigned long nb, char *base,
				t_flags *check_flags);

//%
int			ft_check_percent(char c, t_flags *check_flags);

#endif