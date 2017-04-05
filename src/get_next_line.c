/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 19:07:22 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/26 06:31:28 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

static int		get_next_read(t_line **tab, int const fd)
{
	char	*buf;
	int		ret;
	char	*tmp;

	if (!(buf = (char *)malloc(BUFF_SIZE + 1)))
		return (-1);
	if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		buf[ret] = '\0';
	if (ret == -1 || ret == 0)
	{
		free(buf);
		return (ret);
	}
	tmp = (*tab)->string;
	(*tab)->string = ft_strjoin((*tab)->string, buf);
	ft_strdel(&tmp);
	ft_strdel(&buf);
	(*tab)->size += ret;
	return (1);
}

static int		ft_findbn(char *s, int start, int *i)
{
	*i = 0;
	while (s && s[start + *i])
	{
		if (s[start + *i] == '\n')
		{
			*i += 1;
			return (1);
		}
		*i += 1;
	}
	return (0);
}

static int		ft_read(t_line **tab, int const fd)
{
	char	*buf;
	ssize_t	ret;

	if (!(buf = (char *)malloc(BUFF_SIZE + 1)))
		return (-1);
	if ((ret = read(fd, buf, BUFF_SIZE)) > 0)
		buf[ret] = '\0';
	if (ret == 0 || ret == -1)
	{
		ft_strdel(&buf);
		return (ret);
	}
	if (!(*tab = (t_line *)malloc(sizeof(t_line))))
	{
		ft_strdel(&buf);
		return (-1);
	}
	(*tab)->string = buf;
	(*tab)->i = 0;
	(*tab)->size = ret;
	return (1);
}

static t_line	*ft_split(t_line *tab, char **line, int const fd)
{
	int		i;
	int		ret;
	int		count;

	ret = 1;
	i = 0;
	if (!tab || (count = 0))
		return (NULL);
	while (!ft_findbn(tab->string, tab->i, &i) && (count += 1) && ret != 0)
	{
		if ((ret = get_next_read(&tab, fd)) == -1)
			return (gnl_free(&tab, &tab->string));
	}
	if (i == 0)
		return (gnl_free(&tab, &tab->string));
	if (tab->string[tab->i + i - 1] == '\n')
		*line = ft_strsub(tab->string, tab->i, (tab->i + i) - 1);
	else
		*line = ft_strsub(tab->string, tab->i, (tab->i + i));
	tab->i += i;
	if (count)
		gnl_reset_read_add(&tab);
	return (tab);
}

int				get_next_line(int const fd, char **line)
{
	static void	*first = NULL;
	t_line		*tab;
	int			ret;

	ret = 0;
	tab = NULL;
	if (fd < 0 || (*line = NULL))
		return (-1);
	tab = !first ? NULL : first;
	if (tab && tab->i < tab->size)
		tab = ft_split(tab, line, fd);
	else
	{
		if (tab)
			gnl_free(&tab, &tab->string);
		ret = ft_read(&tab, fd);
		tab = ft_split(tab, line, fd);
	}
	first = tab;
	if (ret < 0)
		return (-1);
	if (!tab || !line)
		return (0);
	return (1);
}
