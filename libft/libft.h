/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbrulin <hbrulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:43:04 by hbrulin           #+#    #+#             */
/*   Updated: 2020/02/28 11:57:01 by hbrulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define BUFFER_SIZE 1

typedef	struct		s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

typedef enum		e_bool
{
	false,
	true
}					t_bool;

void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);
int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *s1);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnjoin(const char *s1, const char *s2, int n);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
int					ft_printf(const char *format, ...);
int					ft_putchar(char c);
void				ft_putstr(char *str);
char				*aff_hex(unsigned long value);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strnew(size_t size);
void				ft_tabdel(void **tab);
char				*ft_uitoa(unsigned int n);
int					get_next_line(int fd, char **line);
size_t				tab_size(char **tab);
int					ft_atoi_base(char *str, char *base);
int					ft_is_space(char c);
size_t				ft_tablen(char **tab);
char				**copy_tab(char **tab);
char				**ft_lst_to_tab(t_list *list);
int					ft_strcmp(const char *s1, const char *s2);
t_list				*ft_tab_to_list(t_list **lst, char **tab);
void				ft_list_sort(t_list *lst);
void				ft_lstprint(t_list *lst);
t_list				*ft_lst_search_n_destroy(t_list *lst, char *key);
void				ft_tab_print(char **tab);
int					ft_tabindex(const char **tab, const char *s);
int					ft_indexr(const char *s, int c);
int					ft_lstiter_n_cmp(t_list *lst, char *arg);
int					ft_lstiter_cmp(t_list *lst, char *arg);
char				**ft_sub_tab(char **tab, int start, int len);
int					ft_tab_chr_i(char **tab, char *arg);
char				**ft_tab_chr(char **tab, char *arg);
int					ft_iter_tab_cmp(char **tab, char *arg);

#endif
