/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 11:55:11 by abarrio-          #+#    #+#             */
/*   Updated: 2024/01/23 11:24:14 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "default_libs.h"
# include "color.h"
# include "ft_printf.h"
# include "get_next_line.h"

// basics
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
void	ft_bzero(void *str, size_t n);
int		ft_toupper(int c);
int		ft_tolower(int c);

// str
int		ft_strlen(const char *str);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_strnstr(const char *text, const char *word, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
int		ft_strcmp(const char *str1, const char *str2);

// mem
void	*ft_memset(void *str, int c, size_t n);
void	*ft_memcpy(void *dest, const void *origen, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(void *buffer, int c, size_t count);
int		ft_memcmp(const void *buffer1, const void *buffer2, size_t count);

// rest
int		ft_atoi(const char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	*ft_free_split(char **memory);
double	ft_atof(char *str);
void	*ft_mfree(int count, ...);

// put
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr(char *s);
void	ft_putchar(char c);

// structs
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif
