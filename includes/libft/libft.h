/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:52:42 by wnocchi           #+#    #+#             */
/*   Updated: 2024/07/23 08:51:51 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include "color.h"
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <inttypes.h>

void	ft_bzero(void *s, size_t n);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strrchr(const char *s, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
int		ft_strcmp(char *s1, char *s2);

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_realloc(void *ptr, size_t size);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *add);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *add);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

//GNL

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*ft_line_cpy(char *s);
char	*ft_new_line(char *buffer);
char	*ft_get_first_line(int fd, char *line);
char	*get_next_line(int fd);
char	*ft_strcat_malloc(char *s1, char *s2);
char	*ft_strchr_gnl(char *s, char to_find);
char	*join_free(char *line, char *buffer);
size_t	ft_strlen_gnl(char *s);
char	*ft_strdup_gnl(char *s);

// ft_printf

int		ft_is_c(char c, int fd);
int		ft_is_di(int nb, int fd);
int		ft_is_p(void *ptr, int fd);
int		ft_is_s(const char *s, int fd);
int		ft_is_u(unsigned int nb, int fd);
int		ft_is_xl(int hexa, int fd);
int		ft_is_xu(int hexa, int fd);
int		ft_mandatory(const char *fmt, va_list args, int fd);
int		ft_printf(int fd, const char *s, ...);
int		ft_putchar_f(char c, int fd);
int		ft_putnbr_base(unsigned int nb, char *base, int fd);
int		ft_putnbr_f(long int nb, int fd);
int		ft_putnbr_base_long(unsigned long nb, char *base, int fd);
int		ft_putstr(char *s);

#endif