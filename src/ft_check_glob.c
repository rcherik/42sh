/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_glob.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/24 13:23:40 by jbail             #+#    #+#             */
/*   Updated: 2014/03/19 15:11:28 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "globbing.h"
#include "curl.h"
#include <stdlib.h>

int		ft_check_slash(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		if (s[i] == '[')
		{
			while (s[i + 1] != ']')
				i++;
			i++;
		}
		i++;
	}
	return (0);
}

int		ft_check_chars(char *s, char *check)
{
	int		i;

	while (*s)
	{
		i = 0;
		while (check[i])
		{
			if (*s == check[i])
				return (1);
			i++;
		}
		s++;
	}
	return (0);
}

int		ft_check_brackets(char *s, char c)
{
	int		i;
	int		len;
	char	*tmp;

	i = (s[0] == '!') ? 1 : 0;
	len = ft_get_bracket_len(s);
	tmp = ft_strnew(0);
	while (i < len)
	{
		if (i + 2 < len && s[i + 1] == '-')
		{
			tmp = ft_add_to_string(s[i], s[i + 2], tmp);
			i += 3;
		}
		else
		{
			tmp = ft_add_c_to_string(s[i], tmp);
			i++;
		}
	}
	len = (s[0] == '!') ? ft_nobrak(len + 2, c, tmp) : ft_brak(len + 2, c, tmp);
	free(tmp);
	return (len);
}

int		ft_check_args_length(char **tab)
{
	int		i;
	int		count;
	char	*err_mess;

	i = 0;
	count = 0;
	err_mess = ft_strdup(tab[0]);
	while (tab[i])
	{
		count += ft_strlen(tab[i]);
		if (count > 200000)
		{
			ft_free_tabcpy(tab);
			return (ft_print_error_free(ARG_LIST_LEN, err_mess));
		}
		i++;
	}
	free(err_mess);
	return (0);
}

char	**ft_no_match(char *s)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * 2);
	tab[0] = ft_remove_bs(s);
	tab[1] = NULL;
	return (tab);
}
