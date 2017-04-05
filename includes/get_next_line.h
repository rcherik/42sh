/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 19:07:24 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 08:48:15 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 4096

# include "libft.h"

typedef struct	s_line
{
	char		*string;
	int			size;
	int			i;
}				t_line;

int				get_next_line(int const fd, char **line);
t_line			*gnl_free(t_line **tab_free, char **free_str);
void			gnl_reset_read_add(t_line **tab);
#endif
