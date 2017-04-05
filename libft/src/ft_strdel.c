/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 20:08:25 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/24 23:15:37 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_strdel(char **as)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = *as;
	if (!as || !tmp)
		return ;
	while (tmp[i])
	{
		tmp[i] = '\0';
		i++;
	}
	tmp[i] = '\0';
	free(tmp);
	*as = NULL;
}
