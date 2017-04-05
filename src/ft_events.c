/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 16:42:08 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/25 06:27:43 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "curl.h"
#include <stdlib.h>

int		ft_events(t_shell *shell, char *tmp, int *c, char *buff)
{
	int		i;

	i = c[3];
	if (((int)ft_strlen(buff) + (int)ft_strlen(shell->buffer)) >= BUFFER)
	{
		free(tmp);
		ft_error2("event designator !-n would exceed the buffer", NULL);
		return (-1);
	}
	ft_bzero(shell->buffer, BUFFER + 1);
	ft_strncpy(shell->buffer, tmp, i - c[0] - 2);
	ft_strncpy(shell->buffer + (i - c[0] - 2), buff, ft_strlen(buff));
	ft_memcpy(shell->buffer + (i - c[0] - 2) + ft_strlen(buff),
			tmp + i, ft_strlen(tmp) - i);
	shell->event = 1;
	free(tmp);
	return (0);
}

int		ft_events2(t_shell *shell, char *tmp, int *c, char *buff)
{
	int		i;

	i = c[2];
	if (((int)ft_strlen(buff) + (int)ft_strlen(shell->buffer)) >= BUFFER)
	{
		free(tmp);
		ft_error2("event designator !n would exceed the buffer", NULL);
		return (-1);
	}
	ft_bzero(shell->buffer, BUFFER + 1);
	ft_strncpy(shell->buffer, tmp, i - c[0] - 1);
	ft_memcpy(shell->buffer + (i - c[0] - 1), buff, ft_strlen(buff));
	ft_memcpy(shell->buffer + (i - c[0] - 1) + ft_strlen(buff), tmp + i,
			ft_strlen(tmp) - i);
	free(tmp);
	shell->event = 1;
	return (0);
}

int		ft_not_event(char *buff, int i)
{
	while ((buff[i] && buff[i] != 39) || (buff[i] == 39 && ft_inhib(buff, i)))
		i++;
	return (i);
}
