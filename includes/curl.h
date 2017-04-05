/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   curl.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/27 19:25:57 by jbail             #+#    #+#             */
/*   Updated: 2014/03/24 16:02:46 by jbail            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURL_H
# define CURL_H
# include <stdlib.h>
# include "libft.h"
# include "shell.h"
# include "globbing.h"

/*
** ft_curl.c
*/

char	*ft_in_curl(char *s, int i);
char	**ft_add_to_curl(char **tab, char *s, int *pos);
char	**ft_get_curl(char **tab, char *s);
char	**ft_start_curl(char *s, int *len);
char	**ft_add_tab_curl(char **t1, char **t2, int len);

/*
** ft_curl_uti.c
*/

int		ft_count_curl(char *s);
int		ft_check_bracket(char *s, int i, int *pos);
int		ft_count_commas(char **tab, char *s);
int		ft_correct_curl(char *s, int i);

/*
** ft_utilities.c
*/

int		ft_tlen(char **tab);
int		ft_inhib(char *s, int pos);
char	*ft_add_c_to_str(char *s, char c);
char	**ft_add_c_to_tab(char **tab, char c);
char	*ft_strjoin_n_free_first(char *s, char *s2);

#endif
