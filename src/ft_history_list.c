/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 15:48:15 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 09:01:12 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include <stdlib.h>

t_hist		*create_h_elem(char *buff)
{
	t_hist		*elem;

	elem = (t_hist *)malloc(sizeof(t_hist));
	if (elem)
	{
		elem->buff = ft_strdup(buff);
		elem->next = NULL;
		elem->prev = NULL;
	}
	return (elem);
}

void		add_history(t_hist **history, t_shell *shell)
{
	t_hist		*elem;

	elem = create_h_elem(shell->cmd);
	if (!*history)
	{
		*history = elem;
		elem->pos = 1;
		return ;
	}
	elem->next = *history;
	elem->pos = (*history)->pos + 1;
	(*history)->prev = elem;
	*history = elem;
}

int			last_history(t_hist **history)
{
	t_hist	*tmp;

	if (!history || !*history)
		return (1);
	tmp = *history;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	*history = tmp;
	return (0);
}

void		remove_elem(t_hist *hist, int num)
{
	t_hist		*tmp;
	t_hist		*tmp2;

	tmp = hist;
	while (tmp)
	{
		if (num == tmp->pos)
		{
			if (tmp->prev)
				tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			tmp2 = tmp;
			free(tmp2->buff);
			tmp = tmp->prev;
			free(tmp2);
			while (tmp != NULL)
			{
				tmp->pos--;
				tmp = tmp->prev;
			}
			return ;
		}
		tmp = tmp->next;
	}
}

char		*browse_history(t_hist **history, t_shell *shel, char flag)
{
	char		*tmp;

	if (!(*history))
		return (NULL);
	else if (flag == 'u')
	{
		if (!(*history)->next)
			return ((*history)->buff);
		tmp = (*history)->buff;
		*history = (*history)->next;
	}
	else
	{
		if (!(*history)->prev || !(*history)->prev->prev)
		{
			*history = (*history)->prev ? (*history)->prev : *history;
			shel->copied = 0;
			return (shel->copy_buffer);
		}
		if (!(*history)->next && ft_strequ((*history)->buff, shel->buffer))
			return ((*history)->prev->buff);
		*history = (*history)->prev;
		tmp = (*history)->prev->buff;
	}
	return (tmp);
}
