/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_bq.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 18:59:37 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 00:23:01 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"
#include "curl.h"

static char		*esc_bquote(char *s)
{
	int			i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] != ' ' && (check_char2(s[i]) || s[i] == 39))
		{
			s = add_bs(s, i, &i);
		}
		i++;
	}
	return (s);
}

static char		*get_bc(char *s, int *x)
{
	int			y;

	x[2] = 0;
	y = x[0] + 1;
	while (s[y])
	{
		if (s[y] == '`' && (ft_inhib(s, y)))
			return ((ft_strsub_len(s, x[0] + 1, x[2])));
		x[2]++;
		y++;
	}
	return (NULL);
}

char			*add_bq(char *s, int *x, char ***env)
{
	char	*bc;
	char	*ret;
	char	*tmp;

	bc = get_bc(s, x);
	tmp = ft_strdup(bc);
	if (!(bc = exec_back_quote(bc, env)))
		bc = ft_strdup(tmp);
	bc = esc_bquote(bc);
	ft_strdel(&tmp);
	ret = ft_strnew(ft_strlen(s) + ft_strlen(bc) - 2);
	ft_strncpy(ret, s, x[0]);
	ft_strncpy(ret + x[0], bc, ft_strlen(bc));
	ret = ft_strjoin_free(&ret, s + x[0] + 2 + x[2]);
	x[0] += ft_strlen(bc) - 1;
	ft_strdel(&bc);
	ft_strdel(&s);
	return (ret);
}
