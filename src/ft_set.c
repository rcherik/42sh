/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 02:26:29 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 10:03:09 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "term42.h"
#include "globbing.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void		put_in_set(t_set *sl, int fd)
{
	ft_putstr_fd("?=0\nGROUP=2013\nPID=", fd);
	ft_putnbr_fd(sl->pid, fd);
	ft_putstr_fd("\nUID=", fd);
	ft_putnbr_fd(sl->uid, fd);
	ft_putstr_fd("\nEUID=", fd);
	ft_putnbr_fd(sl->euid, fd);
	ft_putstr_fd("\nGID=", fd);
	ft_putnbr_fd(sl->gid, fd);
	ft_putstr_fd("\nEGID=", fd);
	ft_putnbr_fd(sl->egid, fd);
	ft_putstr_fd("\nUSER=", fd);
	ft_putstr_fd(sl->user, fd);
	ft_putstr_fd("\nHISTSIZE=500\nHOME=/nfs/zfs-student-4/users/2013/", fd);
	ft_putstr_fd(sl->name, fd);
	ft_putstr_fd("\nPATH=/usr/bin:/bin\nLOGNAME=", fd);
	ft_putstr_fd(sl->name, fd);
	ft_putstr_fd("\nMAIL=", fd);
	ft_putstr_fd(sl->name, fd);
	ft_putstr_fd("@student.42.fr\nPROMPT=$> \nTERM=xterm-256color\n", fd);
	ft_putstr_fd("USERNAME=", fd);
	ft_putstr_fd(sl->name, fd);
	ft_putstr_fd("\nVENDOR=apple\n42SH_NAME=42sh\n", fd);
	ft_putstr_fd("42SH_PATCHLEVEL=OVER9000\nPROMPT_COLOR=4\n", fd);
	ft_putstr_fd("GLOBBING=1\nEVENT_DES=1\n", fd);
}

static void		fill_setl(t_set *sl)
{
	sl->name = ft_strdup(getlogin());
	sl->pid = getpid();
	sl->uid = getuid();
	sl->euid = geteuid();
	sl->gid = getgid();
	sl->egid = getegid();
	sl->user = ft_strdup(getlogin());
}

void			ft_set_set(t_shell *shell)
{
	int			fd;
	t_set		*setl;

	setl = (t_set *)malloc(sizeof(t_set));
	fill_setl(setl);
	fd = open(shell->set_path, O_RDWR | O_CREAT | O_TRUNC, S_IRGRP
			| S_IROTH | S_IRWXU);
	put_in_set(setl, fd);
	ft_strdel(&setl->name);
	ft_strdel(&setl->user);
	free(setl);
	close(fd);
}
