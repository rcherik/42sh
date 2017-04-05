/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/18 19:09:00 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/24 19:27:40 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include <unistd.h>
#include <stdlib.h>

int		list_history(t_hist *hist)
{
	int		space;
	t_hist	*tmp;

	tmp = hist;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		write(1, "     ", 5);
		ft_putnbr(tmp->pos);
		space = tmp->pos;
		write(1, " ", 1);
		while ((space *= 10) < 1000)
			write(1, " ", 1);
		ft_putendl(tmp->buff);
		tmp = tmp->prev;
	}
	return (0);
}

int		free_history(t_hist **list)
{
	t_hist		*tmp;

	while (*list)
	{
		tmp = *list;
		if (tmp->buff)
			ft_strdel(&tmp->buff);
		*list = (*list)->next;
		free(tmp);
	}
	free(*list);
	*list = NULL;
	list = NULL;
	return (0);
}

int		remove_history(t_hist *hist, int num)
{
	t_hist		*tmp;

	tmp = hist;
	while (tmp)
	{
		if (num == tmp->pos)
		{
			ft_putendl(tmp->buff);
			{
				remove_elem(hist, num);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (ft_error("history position out of range", NULL) * -1);
}
