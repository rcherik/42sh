/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globbing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbail <jbail@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/17 16:08:07 by jbail             #+#    #+#             */
/*   Updated: 2014/03/27 17:41:53 by mdufaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBBING_H
# define GLOBBING_H
# include <dirent.h>
# include "libft.h"
# include "shell.h"

# ifndef T_DIRENT
#  define T_DIRENT
typedef struct dirent	t_dirent;
# endif

typedef struct		s_files
{
	char			*file;
	struct s_files	*next;
}					t_files;

/*
** ft_globbing.c
*/

char				**ft_start_globbing(char *s);
int					ft_globbing_add(char *opt, t_files *files, char ***tab);
char				**ft_glob(char *opts, t_files *files);
char				*ft_remove_bs(char *s);

/*
** ft_init_globbing.c
*/

char				*ft_init_globbing(char *s, t_files *files);
t_files				*ft_init_files_dir(char *path, int *err);
t_files				*ft_init_files(char *path);

/*
** ft_match.c
*/

int					ft_match(char *s1, char *s2);
int					ft_first_match(char *s1, char *s2);

/*
** ft_add_to_glob.c
*/

char				*ft_add_c_to_string(char c, char *s);
char				*ft_add_to_string(char c, char c2, char *s);
char				**ft_add_to_opts(char **tab, char *opts);
t_files				*ft_add_to_list(t_files *list, char *s);

/*
** ft_check_glob.c
*/

int					ft_check_slash(char *s);
int					ft_check_args_length(char **tab);
int					ft_check_chars(char *s, char *check);
int					ft_check_brackets(char *s, char c);
char				**ft_no_match(char *s);

/*
** dirs.c
*/

char				**ft_get_dirs(char *path, char *opt, int *match, int *lim);
char				**ft_init_dirs(char *s);
char				**ft_get_new_dirs(char **c_dir, char *old_dir, char **tab);
char				**ft_process_dirs(char **d, char *opt, int *match, int *l);
int					ft_get_files_from_dir(char *s, char ***tab, int *lim);

/*
** ft_free_globbing.c
*/

void				ft_free_files(t_files *files);
char				*ft_strjoin_and_char(char *s1, char *s2, char c);
char				*ft_strjoin_char_free_first(char *s1, char *s2, char c);
char				*ft_end_dir(char **dir, char *s);
char				**ft_free_str_ret_tab(char **s);

/*
** ft_bracket.c
*/

int					ft_brak(int ret, char c, char *s);
int					ft_nobrak(int ret, char c, char *s);
int					ft_get_bracket_len(char *s);

/*
** ft_tab_uti.c
*/

char				**ft_add_tab(char **tab1, char **tab2);
void				ft_free_tabcpy(char **tab);
#endif
