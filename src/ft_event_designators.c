/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_event_designators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 17:59:43 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/26 20:37:41 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "curl.h"
#include <stdlib.h>
#include <unistd.h>

static int		refer_to_n(t_shell *shell, int i)
{
	t_hist		*tmp;
	char		*tmp2;
	int			c[3];

	ft_init_tabint(c, 3);
	tmp2 = ft_strdup(shell->buffer);
	tmp = shell->history;
	while (shell->buffer[i] >= '0' && shell->buffer[i] <= '9')
	{
		c[0] += 1;
		i++;
	}
	c[1] = ft_atoi_free(ft_strsub_len(shell->buffer, i - c[0], c[0]));
	if (!shell->history)
		return (no_event(shell, c[1], tmp2));
	c[2] = i;
	while (tmp != NULL)
	{
		if (c[1] == tmp->pos)
			return (ft_events2(shell, tmp2, c, tmp->buff));
		tmp = tmp->next;
	}
	return (no_event(shell, c[1], tmp2));
}

static int		n_lines_back(t_shell *shell, int i)
{
	t_hist		*tmp;
	char		*tmp2;
	int			c[4];

	ft_init_tabint(c, 3);
	c[3] = i;
	tmp2 = ft_strdup(shell->buffer);
	tmp = shell->history;
	while (shell->buffer[c[3]] >= '0' && shell->buffer[c[3]] <= '9')
	{
		c[0] += 1;
		c[3] += 1;
	}
	c[1] = ft_atoi_free(ft_strsub_len(shell->buffer, c[3] - c[0], c[0]));
	c[2] = c[1];
	if (!shell->history)
		return (no_event(shell, c[1], tmp2));
	while (tmp->next != NULL)
	{
		if (c[1] == 1)
			return (ft_events(shell, tmp2, c, tmp->buff));
		c[1] -= 1;
		tmp = tmp->next;
	}
	return (no_event(shell, c[2], tmp2));
}

static int		ft_last_cmd(t_shell *shell, int i)
{
	t_hist		*tmp;
	char		*tmp2;

	tmp2 = ft_strdup(shell->buffer);
	if (!shell->history)
		return (no_event2(shell, i, tmp2));
	tmp = shell->history;
	if (((int)ft_strlen(tmp->buff) + (int)ft_strlen(shell->buffer)) >= BUFFER)
	{
		free(tmp2);
		ft_error2("event designator !! would exceed the buffer.", NULL);
		return (-1);
	}
	ft_bzero(shell->buffer, BUFFER + 1);
	ft_strncpy(shell->buffer, tmp2, i);
	ft_memcpy(shell->buffer + i, tmp->buff, ft_strlen(tmp->buff));
	ft_memcpy(shell->buffer + i + ft_strlen(tmp->buff), tmp2 + i + 2,
			ft_strlen(tmp2) - i - 2);
	shell->event = 1;
	free(tmp2);
	return (0);
}

static int		get_events2(t_shell *shell, int *c)
{
	if (shell->buffer[c[0] + 1] == '!')
		c[1] = ft_last_cmd(shell, c[0]);
	if (shell->buffer[c[0] + 1] == '!')
		c[0] += 2;
	else if (ft_isdigit(shell->buffer[c[0] + 1]))
		c[1] = refer_to_n(shell, c[0] + 1);
	else if (shell->buffer[c[0] + 1] == '-'
			&& ft_isdigit(shell->buffer[c[0] + 2]))
		c[1] = n_lines_back(shell, c[0] + 2);
	else if (shell->buffer[c[0] + 1] == '#')
	{
		c[1] = ft_sharp(shell, c[0]);
		c[0] += 1;
	}
	return (c[1]);
}

int				get_events(t_shell *shell)
{
	int			c[2];

	ft_init_tabint(c, 2);
	if (shell->set_opt[EVENT_DES] == 0)
		return (c[1]);
	while (shell->buffer[c[0]])
	{
		if (shell->buffer[c[0]] == 39)
			c[0] = ft_not_event(shell->buffer, c[0]);
		if (shell->buffer[c[0]] == '!' && ft_inhib(shell->buffer, c[0]))
			c[1] = get_events2(shell, c);
		if (c[1] < 0)
			return (c[1]);
		c[0] += 1;
	}
	if (shell->event == 1)
	{
		write(1, "\n", 1);
		ft_putstr(shell->buffer);
	}
	return (c[1]);
}
