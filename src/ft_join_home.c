/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/18 15:45:16 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 09:02:21 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "shell.h"
#include "stdlib.h"

char		*ft_join_home(char *s, t_shell *sh)
{
	char		*ret;
	char		*h;

	if ((h = ft_get_env(sh->env, "HOME")) == NULL)
		return (s);
	ret = ft_strjoin(h, s + 1);
	free(h);
	free(s);
	return (ret);
}

void		ft_rotate(t_shell *sh, char *sch, char *path, int count)
{
	free(path);
	free(sch);
	ft_perform_rotation(sh);
	if (count)
		sh->copy_comp = ft_strdup(sh->buffer);
}

int			put_in_list(t_dirent *ent, char *sch, int ct, t_shell *sh)
{
	if ((ft_strcmp(ent->d_name, ".") && ft_strcmp(ent->d_name, "..")))
	{
		if (!(ft_strncmp(ent->d_name, sch, ft_strlen(sch)))
				&& !(!*sch && !ft_strncmp(ent->d_name, ".", 1)))
		{
			ft_next_comp(&sh->comp, ent->d_name + ft_strlen(sch),
			ent->d_type);
			ct++;
		}
	}
	return (ct);
}
