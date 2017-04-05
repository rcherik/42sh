/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_completion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/22 21:05:33 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/18 19:22:31 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"

void		ft_perform_rotation(t_shell *shell)
{
	t_comp	*tmp;

	if (!shell->comp)
		return ;
	tmp = shell->comp;
	while (shell->comp->next)
		shell->comp = shell->comp->next;
	shell->comp->next = tmp;
	tmp->prev = shell->comp;
	shell->comp = tmp;
}

static void	first_tab(t_shell *shell, char **buff)
{
	char		*sch;
	int			count;

	count = 0;
	sch = NULL;
	if (shell->buffer[ft_strlen(shell->buffer) - 1] == ' ')
	{
		create_dot_list(".", shell);
		ft_display_comp(shell);
	}
	else
	{
		create_comp_list(shell, buff[ft_tablen(buff) - 1], sch, count);
		ft_display_comp(shell);
	}
}

static void	start_completion(t_shell *shell, char **buff)
{
	if (!shell->comp)
		first_tab(shell, buff);
	else
		ft_display_comp(shell);
}

void		ft_completion(t_shell *shell)
{
	char	**buff;

	buff = ft_strsplit(shell->buffer, ' ');
	if (!buff)
		return ;
	if (!*buff)
	{
		ft_free_tab(&buff);
		return ;
	}
	start_completion(shell, buff);
	ft_free_tab(&buff);
}
