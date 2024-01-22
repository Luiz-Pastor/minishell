/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:26:15 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 16:22:32 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*auxnode;

	if (!lst || !f)
		return ;
	auxnode = lst;
	while (auxnode != NULL)
	{
		f(auxnode->content);
		auxnode = auxnode->next;
	}
}
