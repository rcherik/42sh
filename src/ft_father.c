/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_father.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 15:22:04 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 15:25:12 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include <unistd.h>

int		am_father(void)
{
	t_shell	*shell;

	shell = ft_return_shell(NULL, NULL);
	if (shell->pid == getpid())
		return (1);
	return (0);
}
