/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunze <hyunze@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 14:15:14 by hann              #+#    #+#             */
/*   Updated: 2020/08/30 14:31:29 by hyunze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif

# ifndef MAX_FD
#  define MAX_FD 10000
# endif

# define SUCCESS 1
# define EOF 0
# define ERROR -1

int		get_next_line(int fd, char **line);

int		ft_strlen(char *c);
char	*ft_strncpy(char *dst, char *src, int n);
char	*ft_strchr(char *s, int c);
char	*ft_strndup(char *s1, int size);
char	*ft_strjoin(char *s1, char *s2);

#endif
