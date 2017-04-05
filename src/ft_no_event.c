/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_no_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 16:51:52 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/19 22:24:27 by tlesven          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "error_code.h"
#include <stdlib.h>

int			no_event(t_shell *shell, int n, char *tmp2)
{
	char		*tmp;
	char		*tmp3;

	tmp = ft_strdup(shell->buffer);
	ft_bzero(shell->buffer, BUFFER + 1);
	tmp3 = ft_itoa(n);
	ft_error2("no such event: ", tmp3);
	free(tmp);
	free(tmp2);
	free(tmp3);
	if (shell->buffer[0] == '\0')
		return (-1);
	return (0);
}

int			no_event2(t_shell *shell, int i, char *tmp2)
{
	char		*tmp;

	free(tmp2);
	tmp = ft_strdup(shell->buffer);
	ft_bzero(shell->buffer, BUFFER + 1);
	ft_strncpy(shell->buffer, tmp, i);
	ft_error2("no such event", NULL);
	free(tmp);
	if (shell->buffer[0] == '\0')
		return (-1);
	return (-1);
}
