/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 15:54:14 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:11:08 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void    ft_del_content(void *content)
{
    free(content);
}
*/
void	ft_lstclear(t_list **list, void (*del)(void *))
{
	t_list	*node;
	t_list	*temp;

	node = *list;
	if (list == NULL || *list == NULL)
		return ;
	while (node != NULL)
	{
		temp = node -> next;
		ft_lstdelone(node, del);
		node = temp;
	}
	*list = NULL;
}
