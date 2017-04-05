/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display_comp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 17:23:57 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/23 20:05:17 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include <stdlib.h>

static void		ft_print(t_shell *shell, char *tmp, char *tmp2)
{
	free(tmp);
	free(tmp2);
	ft_home(shell);
	ft_exec_termcaps("cd");
	shell->cursor_pos = ft_strlen(shell->buffer);
	ft_putstr(shell->buffer);
}

void			ft_display_comp(t_shell *shell)
{
	char		*tmp;
	char		*tmp2;
	t_comp		*tmp3;

	if (!shell->comp)
		return ;
	tmp3 = shell->comp;
	tmp = ft_strdup(shell->copy_comp);
	ft_bzero(shell->buffer, BUFFER + 1);
	tmp3 = tmp3->next;
	while (((int)ft_strlen(tmp3->s) + (int)ft_strlen(tmp)) >= BUFFER)
		tmp3 = tmp3->next;
	tmp2 = ft_strjoin(tmp, tmp3->s);
	ft_strcpy(shell->buffer, tmp2);
	ft_print(shell, tmp, tmp2);
	shell->comp = tmp3;
}
