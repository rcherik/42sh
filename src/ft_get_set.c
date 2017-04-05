/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 04:42:38 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 13:09:14 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term42.h"
#include <unistd.h>
#include <fcntl.h>

static char		*ft_get_path(void)
{
	t_shell	*shell;

	shell = ft_return_shell(NULL, NULL);
	if (!shell)
		return (NULL);
	return (shell->set_path);
}

static char		*get_wanted(char *w)
{
	int			i;
	char		*ret;

	i = 0;
	while (w[i])
	{
		if (w[i] == '=')
		{
			ret = (ft_strsub_len(w, i + 1, ft_strlen(w) - i));
			return (ret);
		}
		i++;
	}
	return (NULL);
}

char			*ft_get_set(char *want)
{
	char		*l;
	int			fd;
	char		*ret;

	ret = NULL;
	fd = open(ft_get_path(), O_RDONLY);
	if (!want || !*want)
		return (NULL);
	while (get_next_line(fd, &l) > 0)
	{
		if (!ret && !ft_strncmp(l, want, ft_strclen(l, '=')))
			ret = get_wanted(l);
		ft_strdel(&l);
	}
	if (fd > 0)
		close(fd);
	ft_strdel(&want);
	return (ret);
}
