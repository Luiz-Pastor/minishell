/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angela <angela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:59:50 by abarrio-          #+#    #+#             */
/*   Updated: 2023/12/20 13:32:51 by angela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "default_libs.h"

char	*get_next_line(int fd);
void	*ft_gnl_free(char *buff, char *aux);
int		ft_gnl_strlen(const char *str);
char	*ft_gnl_strjoin(char *s1, char *s2);
char	*ft_gnl_strchr(const char *s, int c);
char	*ft_gnl_strdup(const char *src);
char	*ft_gnl_substr(char *s, unsigned int start, size_t len);

#endif
