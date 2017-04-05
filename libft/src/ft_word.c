/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/26 16:31:03 by mdufaud           #+#    #+#             */
/*   Updated: 2014/02/07 02:09:59 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_word_size(char *s, int start)
{
	int	i;
	int	j;

	i = 0;
	j = start;
	if (ft_isspace(s[start]))
		return (start);
	while (!ft_isspace(s[j]) && s[j])
	{
		j++;
		i++;
	}
	return (i);
}

int		ft_get_next_word(char *s, int i)
{
	int	tmp;

	tmp = i;
	if (!s)
		return (-1);
	while (!ft_isspace(s[i]) && s[i])
		i++;
	while (ft_isspace(s[i]) && s[i])
		i++;
	if (!ft_isspace(s[i]) || !ft_isspace(s[i - 1]))
		return (i);
	else
		return (tmp);
}
