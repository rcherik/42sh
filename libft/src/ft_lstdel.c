/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 19:19:45 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/12 23:01:48 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*lst;

	while (*alst && del)
	{
		lst = ft_lstnew((*alst)->content, (*alst)->content_size);
		(*alst) = (*alst)->next;
		(*del)(lst->content, lst->content_size);
		free(lst);
		lst = NULL;
	}
}
