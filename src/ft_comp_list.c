/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_comp_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 16:45:51 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 09:00:15 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "shell.h"
#include <stdlib.h>

t_comp		*cr_comp_list(char *s, char type)
{
	t_comp		*head;
	char		*str;

	if (!(head = (t_comp *)malloc(sizeof(t_comp))))
		return (NULL);
	head->type = type;
	str = (type == DT_DIR) ? ft_strjoin(s, "/") : ft_strdup(s);
	if (!str)
	{
		free(head);
		return (NULL);
	}
	head->s = NULL;
	if (!(head->s = check_spe_char(str)))
		head->s = str;
	head->head = NULL;
	head->prev = NULL;
	head->next = NULL;
	head->len = 0;
	return (head);
}

void		ft_next_comp(t_comp **comp, char *s, char c)
{
	t_comp		*new;

	new = cr_comp_list(s, c);
	if ((*comp))
	{
		new->next = (*comp);
		new->head = (*comp)->head;
		(*comp)->prev = new;
	}
	else
	{
		new->next = (*comp);
		new->head = new;
	}
	(*comp) = new;
	if ((*comp)->head)
		(*comp)->head->len += 1;
}

void		create_dot_list(char *path, t_shell *shell)
{
	DIR			*dir;
	t_dirent	*ent;
	int			count;

	count = 0;
	if ((dir = opendir(path)) == NULL)
		return ;
	shell->comp = NULL;
	while ((ent = readdir(dir)) != NULL)
	{
		if (!(ft_strnequ(ent->d_name, ".", 1) || ft_strequ(ent->d_name, "..")))
		{
			count++;
			ft_next_comp(&shell->comp, ent->d_name, ent->d_type);
		}
	}
	if (count)
		shell->copy_comp = ft_strdup(shell->buffer);
	ft_perform_rotation(shell);
	closedir(dir);
}

char		*get_paths(char *s, int flag)
{
	int		i;

	i = ft_strlen(s);
	if (!s)
		return (NULL);
	if (ft_strnchar(s, '/') == 0)
	{
		if (flag == 1)
			free(s);
		return (ft_strdup("."));
	}
	i--;
	while (s && i >= 0)
	{
		if (s[i] == '/')
		{
			if (flag == 1)
				free(s);
			return (ft_strsub_len(s, 0, i + 1));
		}
		i--;
	}
	if (flag == 1)
		free(s);
	return (s);
}

void		create_comp_list(t_shell *s, char *p, char *sch, int count)
{
	t_dirent	*ent;
	DIR			*dir;
	char		*path;

	if (p[0] == '~' && p[1] && p[1] == '/')
	{
		path = get_paths((ft_join_home(ft_strdup(p), s)), 1);
		sch = ft_strsub_free(ft_strdup(p), 0, ft_strlen(sch) - 1);
	}
	else
		path = get_paths(p, 0);
	if ((dir = opendir(path)) == NULL)
	{
		free(path);
		return ;
	}
	s->comp = NULL;
	if ((!(ft_strcmp(".", path)) && !sch))
		sch = ft_strdup(p);
	else if (!sch)
		sch = ft_strsub_len(p, ft_strlen(path), ft_strlen(p) - ft_strlen(path));
	while ((ent = readdir(dir)) != NULL)
		count = put_in_list(ent, sch, count, s);
	ft_rotate(s, sch, path, count);
	closedir(dir);
}
