/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miouali <miouali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:00:41 by miouali           #+#    #+#             */
/*   Updated: 2026/02/05 14:37:44 by miouali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stddef.h>
# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <strings.h>
# include <limits.h>
# include <stdarg.h>

//ft_printf

int			ft_size_base(long long int n, int len_base);
int			ft_format_d(va_list ap);
int			ft_format_s(va_list ap);
int			ft_format_u(va_list ap);
int			ft_format_big_x(va_list ap);
int			ft_format_x(va_list ap);
int			ft_format_c(va_list ap);
int			ft_format_percent(va_list ap);
int			ft_printf(const char *prototype, ...);
int			ft_format_p(va_list ap);
int			ft_format_i(va_list ap);

typedef int				(*t_format)(va_list);

typedef struct format_stuct
{
	char		letter;
	t_format	format_alias;
}	t_alias;
/*40: Definition of a structure using typedef.
42: We will need it for comparison.
43: Alias used to call a function.
44: Complete structure alias.*/
extern const t_alias	g_format_tab[];

//gnl

size_t		ft_strlen_gnl(const char *src);
char		*get_next_line(int fd);
char		*ft_substr_gnl(char const *s, unsigned int start, size_t len);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
int			ft_strchr_gnl(char *s, int c);

// IS
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);

//lst

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list		*ft_lstnew(void *content);
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void*));
void		ft_lstclear(t_list **list, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);

//mem

void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void		*ft_print_memory(void *addr, unsigned int size);
void		ft_bzero(void *s, size_t n);
void		ft_free_str_tab(char **tab);
int			ft_memcmp(const void *s1, const void *s2, size_t n);

//put

void		ft_putchar_fd(char c, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *str, int fd);
int			ft_putnbr_base(int n, char *base);

//str

char		**ft_split(char const *s, char c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strjoin_free(char *s1, char *s2, int mode);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));

//to

double		ft_atof(const char *str);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *s);
int			ft_toupper(int c);
int			ft_tolower(int c);
int			ft_atoi(const char *str);

//maths

double		ft_pow(double nb, int power);
int			ft_sqrt(int nb);

#endif
