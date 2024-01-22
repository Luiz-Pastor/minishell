/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:13:55 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:22:41 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_lstsize(t_list *lst)
{
	int	nb;

	nb = 0;
	if (!lst)
		return (0);
	while (lst != NULL)
	{
		lst = lst->next;
		nb++;
	}
	return (nb);
}
