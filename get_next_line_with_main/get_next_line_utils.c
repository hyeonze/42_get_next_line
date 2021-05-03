/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:      <            >                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/30 14:16:30 by                   #+#    #+#             */
/*   Updated: 2020/08/30 14:16:48 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(char *s)
{
	int	len;

	len = -1;
	while (s[++len])
		;
	return (len);
}

char	*ft_strncpy(char *dst, char *src, int n)
{
	int	i;

	if (dst == 0)
		return (NULL);
	i = -1;
	while (++i < n)
		dst[i] = src[i];
	return (dst);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	if (s == 0)
		return (0);
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	i = -1;
	while (s[++i])
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
	return (0);
}

char	*ft_strndup(char *s1, int size)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (dup == 0)
		return (0);
	ft_strncpy(dup, s1, size);
	dup[size] = 0;
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s_new;
	int		len1;
	int		len2;

	if (s1 == 0 && s2 == 0)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s_new = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (s_new == 0)
		return (0);
	ft_strncpy(s_new, s1, len1);
	ft_strncpy(s_new + len1, s2, len2);
	s_new[len1 + len2] = 0;
	return (s_new);
}
