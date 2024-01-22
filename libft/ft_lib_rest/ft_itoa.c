/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:42:26 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:21:50 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_countnb(int n)
{
	int	nb;

	nb = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		nb++;
	}
	return (nb);
}

static char	*ft_strreverse(char *str, int nb)
{
	int		j;
	int		i;
	char	aux;

	i = 0;
	if (str[i] == '-')
		i++;
	j = nb - 1;
	while (i < j)
	{
		aux = str[i];
		str[i] = str[j];
		str[j] = aux;
		i++;
		j--;
	}
	return (str);
}

static char	*string(char *memory, int sing, int nb, int n)
{
	int	i;

	memory = (char *)malloc((nb + 1) * sizeof(char));
	if (memory == NULL)
		return (NULL);
	i = 0;
	if (sing == -1)
	{
		memory[i] = '-';
		i++;
	}
	while (i < nb)
	{
		memory[i] = (n % 10) + '0';
		i++;
		n = n / 10;
	}
	memory[i] = '\0';
	return (memory);
}

char	*ft_itoa(int n)
{
	int		nb;
	int		sing;
	char	*memory;

	sing = 1;
	nb = 0;
	memory = NULL;
	if (n < 0)
	{
		nb = nb + 1;
		sing = -1;
		n = n * -1;
	}
	nb = ft_countnb(n) + nb;
	if (n == -2147483648)
	{
		memory = ft_strdup(((const char *)"-2147483648"));
		return (memory);
	}
	memory = string(memory, sing, nb, n);
	if (!memory)
		return (NULL);
	memory = ft_strreverse(memory, nb);
	return (memory);
}
