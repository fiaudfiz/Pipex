/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:15:42 by miouali           #+#    #+#             */
/*   Updated: 2026/02/02 10:13:12 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
void *ft_print_content(void *content)
{
    char *s = (char *)content;
    printf("[Contenu: %s] ", s);
	return(content);
}

void    ft_del_content(void *content)
{
    free(content);
}
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*dest;
	void	*new_content;

	if (!lst || !f || !del)
		return (NULL);
	dest = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new = ft_lstnew(new_content);
		if (!new)
		{
			if (new_content)
			{
				del(new_content);
			}
			ft_lstclear(&dest, del);
			return (NULL);
		}
		ft_lstadd_back(&dest, new);
		lst = lst->next;
	}
	return (dest);
}
