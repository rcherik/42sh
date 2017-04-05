/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/22 12:13:34 by mdufaud           #+#    #+#             */
/*   Updated: 2014/01/22 12:15:31 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r' ||
			c == ' ')
		return (1);
	else
		return (0);
}
