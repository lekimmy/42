/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ls-phabm <ls-phabm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:26:49 by ls-phabm          #+#    #+#             */
/*   Updated: 2025/11/21 20:19:40 by ls-phabm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dup_list;
	t_list	*node;
	void	*new_content;

	if (!lst || !f)
		return (NULL);
	dup_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		node = ft_lstnew(new_content);
		if (!node)
		{
			del(new_content);
			ft_lstclear(&dup_list, del);
			return (NULL);
		}
		ft_lstadd_back(&dup_list, node);
		lst = lst->next;
	}
	return (dup_list);
}
