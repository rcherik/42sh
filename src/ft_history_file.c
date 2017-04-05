/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 15:55:22 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 12:11:25 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "error_code.h"
#include <stdlib.h>
#include <unistd.h>

char	*get_hist_file(void)
{
	t_shell	*shell;

	shell = ft_return_shell(NULL, NULL);
	return (shell->hist_name);
}

int		hist_to_file(t_hist *hist)
{
	t_hist		*tmp;
	int			fd;
	int			count;

	count = 0;
	tmp = hist;
	if ((fd = open(get_hist_file(), O_CREAT | O_TRUNC, S_IRGRP
					| S_IROTH | S_IRWXU)) == -1)
		return (-1);
	close(fd);
	if ((fd = open(get_hist_file(), O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU
					| S_IRGRP | S_IROTH)) == -1)
		return (-1);
	while (tmp && tmp->next && count++ < MAX_HIST_FILE)
		tmp = tmp->next;
	count = 0;
	while (tmp && count < MAX_HIST_FILE)
	{
		count++;
		ft_putendl_fd(tmp->buff, fd);
		tmp = tmp->prev;
	}
	close(fd);
	return (0);
}

int		clear_file(void)
{
	int	fd;

	if ((fd = open(get_hist_file(), O_RDONLY)) == -1)
		return (ft_error("not yet initialized ", get_hist_file()) * -1);
	close(fd);
	if ((fd = open(get_hist_file(), O_CREAT | O_TRUNC,
				S_IRWXU | S_IRGRP | S_IROTH)) == -1)
		return (-1);
	close(fd);
	return (0);
}

int		list_file(void)
{
	int		fd;
	char	*line;

	if (access(get_hist_file(), F_OK) == -1)
		return (ft_error("not yet initialized ", get_hist_file()) * -1);
	if ((fd = open(get_hist_file(), O_RDONLY)) < 0)
		return (ft_error(PERM_DENY, get_hist_file()) * -1);
	else
	{
		while (get_next_line(fd, &line) > 0)
		{
			ft_putendl(line);
			free(line);
		}
	}
	close(fd);
	return (0);
}

void	ft_get_hist_file(t_shell *shell)
{
	char	*l;
	int		fd;
	int		count;

	if ((fd = open(get_hist_file(), O_RDONLY)) < 0)
		return ;
	else
	{
		count = 0;
		while ((get_next_line(fd, &l) > 0) && count < 500)
		{
			if (!(ft_strlen(l) > BUFFER))
			{
				shell->cmd = l;
				add_history(&shell->history, shell);
				ft_strdel(&shell->cmd);
				count++;
			}
			else
				ft_strdel(&l);
		}
	}
	close(fd);
}
