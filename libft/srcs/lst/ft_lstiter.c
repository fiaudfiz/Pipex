/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:07:18 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:11:56 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void ft_print_content(void *content)
{
    char *s = (char *)content;
    printf("[Contenu: %s] ", s);
}
*/
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*node;

	node = lst;
	if (lst == NULL || f == NULL)
		return ;
	while (node != NULL)
	{
		f(node -> content);
		node = node -> next;
	}
}
