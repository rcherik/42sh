/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spe_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/02 19:43:54 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/19 19:41:16 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include <stdlib.h>

static t_comp	*ft_get_first(t_comp *tmp)
{
	while (tmp && tmp != tmp->head)
		tmp = tmp->next;
	tmp = tmp->next;
	return (tmp);
}

void			ft_free_comp(t_shell **shell)
{
	t_comp	*tmp;

	if ((*shell)->comp)
	{
		(*shell)->comp = ft_get_first((*shell)->comp);
		if ((*shell)->copy_comp)
			free((*shell)->copy_comp);
		while ((*shell)->comp && (*shell)->comp != (*shell)->comp->head)
		{
			tmp = (*shell)->comp;
			ft_strdel(&tmp->s);
			(*shell)->comp = (*shell)->comp->next;
			free(tmp);
		}
		ft_strdel(&(*shell)->comp->s);
	}
	free((*shell)->comp);
	(*shell)->comp = NULL;
}

void			ft_d_str_free(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

void			ft_spe_list(char *path, char *sch, t_shell *shell)
{
	DIR			*dir;
	t_dirent	*ent;

	if ((dir = opendir(path)) == NULL)
		return ;
	shell->comp = cr_comp_list(NULL, 0);
	shell->copy_comp = ft_strdup(shell->buffer);
	while ((ent = readdir(dir)) != NULL)
	{
		if (!(ft_strnequ(ent->d_name, ".", 1) || ft_strequ(ent->d_name, "..")))
		{
			if (!(ft_strncmp(ent->d_name, sch, ft_strlen(sch))))
				ft_next_comp(&shell->comp, ent->d_name + ft_strlen(sch),
						ent->d_type);
		}
	}
}
