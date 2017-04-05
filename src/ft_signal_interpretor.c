/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_interpretor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 19:04:05 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/25 19:18:18 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int		ft_signal_interpretor(int sig)
{
	int	signal_n;

	signal_n = 128;
	if (sig == signal_n + SIGSEGV)
		ft_error(SEG_FAULT, NULL);
	if (sig == signal_n + SIGFPE)
		ft_error(FLOAT_P_EXCEPT, NULL);
	if (sig == signal_n + SIGPIPE)
		ft_error(BROKEN_PIPE, NULL);
	if (sig == signal_n + SIGBUS)
		ft_error(BUS_ERROR, NULL);
	return (sig);
}
