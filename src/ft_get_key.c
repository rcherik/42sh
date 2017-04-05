/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcherik <rcherik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 18:56:17 by rcherik           #+#    #+#             */
/*   Updated: 2014/03/27 08:40:03 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "term42.h"

static const t_key	g_tab_keys[] = {

	{
		"\x0A\0\0\0\0", &ft_return
	},
	{
		"\x09\0\0\0\0", &ft_completion
	},
	{
		"\x04\0\0\0\0", &ft_ctrl_d
	},
	{
		"\x7f\0\0\0\0", &ft_back_del
	},
	{
		"\x1b\x5b\x33\x7e\0", &ft_del
	},
	{
		"\x1b\x5b\x41\0\0", &ft_up
	},
	{
		"\x1b\x5b\x42\0\0", &ft_down
	},
	{
		"\x1b\x5b\x43\0\0", &ft_right
	},
	{
		"\x1b\x5b\x44\0\0", &ft_left
	},
	{
		"\x1b\x5b\x48\0\0", &ft_home
	},
	{
		"\x1b\x5b\x46\0\0", &ft_end
	},
	{
		"\x1b\x1b\x5b\x41\0", &ft_alt_up
	},
	{
		"\x1b\x1b\x5b\x42\0", &ft_alt_down
	},
	{
		"\x1b\x1b\x5b\x43\0", &ft_alt_right
	},
	{
		"\x1b\x1b\x5b\x44\0", &ft_alt_left
	}
};

static t_key		*tab_keys(void)
{
	t_key		*tab_keys;

	tab_keys = (t_key *)g_tab_keys;
	return (tab_keys);
}

int					ft_get_key(t_shell *shell)
{
	int					i;
	const t_key			*keys = tab_keys();

	i = 0;
	while (i < 15)
	{
		if (ft_memcmp(shell->key, keys[i].key_code, 4) == 0)
		{
			if (ft_memcmp(keys[i].key_code, "\x09\0\0\0\0", 4))
				ft_free_comp(&shell);
			keys[i].f(shell);
			return (0);
		}
		i++;
	}
	ft_free_comp(&shell);
	ft_display(shell);
	return (0);
}
