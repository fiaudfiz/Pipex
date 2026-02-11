/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:27:53 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:09:49 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (*lst == NULL)
	{
		ft_lstadd_front(lst, new);
		return ;
	}
	node = *lst;
	while (node -> next != NULL)
	{
		node = node -> next;
	}
	node -> next = new;
	new -> next = NULL;
}
