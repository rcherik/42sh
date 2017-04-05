/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 19:31:00 by mdufaud           #+#    #+#             */
/*   Updated: 2014/03/27 09:44:55 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "debug.h"
# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_print_green(char *s);
void				ft_print_greenendl(char *s);
void				ft_putswag(char *s);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
void				ft_putendl(char const *s);
void				ft_print_tab(char **tab);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_print_list(int *l, unsigned int size);
void				ft_putdstr(char *s1, char *s2);
void				ft_putdendl(char *s1, char *s2);
void				ft_putdstr_fd(char *s1, char *s2, int fd);
void				ft_putdendl_fd(char *s1, char *s2, int fd);
void				ft_putcstr(char *s, char *color);
void				ft_putcstr_fd(char *s, int fd, char *color);
void				ft_putcendl(char *s, char *color);
void				ft_putcendl_fd(char *s, int fd, char *color);
void				ft_print_tab_fd(char **tab, int fd);
void				ft_putendltab(char *s);
int					ft_atoi(const char *str);
int					ft_atoi_free(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
int					ft_strclen(char *s, int n);
int					ft_strnchar(char *s, int n);
int					ft_get_next_word(char *s, int i);
int					ft_word_size(char *s, int start);
int					ft_strdigit(char *s);
char				*ft_itoa(int n);
char				*ft_strdup(const char *s);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strncpy(char *s1, const char *s2, size_t n);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
char				*ft_strtcat(char *s1, const char *s2, const char *s3);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strnstr(const char *s1, const char *s2, size_t n);
char				*ft_strnew(size_t size);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strsub_len(char const *s, int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtjoin(char *s1, char *s2, char *s3);
char				*ft_strjoin_c(char const *s1, char const *s2, char c);
char				*ft_strjoin_c_free(char **s1, char const *s2, char c);
char				*ft_strjoin_free(char **s, char const *s2);
char				*ft_strtrim(char *s);
char				**ft_str_all_split(char const *s, char c);
char				**ft_strsplit(char const *s, char c);
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strdup_free(char *s);
char				*ft_strsub_free(char *s, size_t start, size_t len);
char				*ft_sub(char *s, int start, int end);
char				*ft_epur(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_swap_s(char **s1, char **s2);
void				ft_double_free(char *s1, char *s2);
void				ft_triple_del(char *q, char *w, char *e);
size_t				ft_strlen(const char *s);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_isspace(char c);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *s1, const void *s2, size_t n);
void				*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void				*ft_memmove(void *s1, const void *s2, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
int					ft_tablen(char **tab);
int					ft_2dlen(char **tab);
char				**ft_tab_new(size_t col, size_t line);
char				**ft_tabdup(char **tab);
char				**ft_addtab(char **tab, char *s);
void				ft_free_tab(char ***tab);
#endif
