/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 16:01:31 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/24 22:09:45 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void			ft_free_shell(t_shell *shell)
{
	hist_to_file(shell->history);
	ft_free_env(shell->env);
	free_history(&shell->history);
	if (shell->copy_buffer)
		free(shell->copy_buffer);
	if (shell->prompt)
		free(shell->prompt);
	if (shell->comp)
		free(shell->comp);
	free(shell->key);
	free(shell->buffer);
	free(shell);
	ft_exit_term();
}

void			ft_ctrl_d(t_shell *shell)
{
	ft_free_shell(shell);
	ft_putchar('\n');
	_exit(1);
}
