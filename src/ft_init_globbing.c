/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_globbing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 13:20:14 by jbail             #+#    #+#             */
/*   Updated: 2014/03/27 17:54:39 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"
#include "curl.h"

static t_files	*ft_end_files_dir(t_dirent *ent, DIR *dir, int len, int *err)
{
	t_files		*files;

	files = NULL;
	while ((ent = readdir(dir)) != NULL)
	{
		if (!(ft_strequ(ent->d_name, ".") || ft_strequ(ent->d_name, "..")))
		{
			*err += len + ft_strlen(ent->d_name);
			if (*err > 200000)
			{
				*err = -1;
				ft_free_files(files);
				closedir(dir);
				return (NULL);
			}
			files = ft_add_to_list(files, ent->d_name);
		}
	}
	return (files);
}

t_files			*ft_init_files_dir(char *path, int *err)
{
	DIR			*dir;
	char		*s;
	t_dirent	*ent;
	t_files		*files;
	int			len;

	files = NULL;
	ent = NULL;
	len = ft_strlen(path);
	s = (path[0] != '/') ? ft_strjoin("./", path) : ft_strdup(path);
	if ((dir = opendir(s)) == NULL)
	{
		free(s);
		return (NULL);
	}
	if (((files = ft_end_files_dir(ent, dir, len, err)) == NULL) && *err == -1)
	{
		free(s);
		return (NULL);
	}
	free(s);
	closedir(dir);
	return (files);
}

t_files			*ft_init_files(char *path)
{
	DIR			*dir;
	char		*s;
	t_dirent	*ent;
	t_files		*files;

	files = NULL;
	if (path[0] != '/')
		s = ft_strjoin("./", path);
	else
		s = ft_strdup(path);
	if ((dir = opendir(s)) == NULL)
	{
		free(s);
		return (NULL);
	}
	while ((ent = readdir(dir)) != NULL)
	{
		if (!(ft_strequ(ent->d_name, ".") || ft_strequ(ent->d_name, "..")))
			files = ft_add_to_list(files, ent->d_name);
	}
	free(s);
	closedir(dir);
	return (files);
}
