/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:45:39 by tosuman           #+#    #+#             */
/*   Updated: 2024/03/10 18:06:26 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_strcmp(char const *s1, char const *s2)
{
	unsigned char	*us1;
	unsigned char	*us2;

	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	while (*us1 && *us2 && *us1 == *us2)
	{
		++us1;
		++us2;
	}
	return (*us1 - *us2);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = 0;
	while (len + 1 < size && src[len])
		*dst++ = src[len++];
	if (size)
		*dst = 0;
	while (src[len])
		len++;
	return (len);
}

size_t	ft_strlen(char *s)
{
	size_t	length;

	length = 0;
	while (*s++)
		length++;
	return (length);
}

char	*ft_strdup(char *s)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s);
	s2 = malloc(sizeof(*s2) * (len + 1));
	if (!s2)
		return (0);
	ft_strlcpy(s2, (char *)s, len + 1);
	return (s2);
}

int	ft_char_in_charset(char c, char const *charset)
{
	while (*charset)
		if (*charset++ == c)
			return (1);
	return (0);
}

static size_t	len_after_trim(char const *s1, char const *set)
{
	size_t	idx;
	size_t	start;
	size_t	end;

	idx = 0;
	while (ft_char_in_charset(s1[idx], set))
		++idx;
	if (!s1[idx])
		return (0);
	start = idx;
	while (s1[idx])
		++idx;
	--idx;
	while (ft_char_in_charset(s1[idx], set))
		--idx;
	end = idx;
	return (end - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	trimmed_len;
	char	*trimmed_str;

	trimmed_len = len_after_trim(s1, set);
	trimmed_str = malloc(sizeof(*trimmed_str) * (trimmed_len + 1));
	if (!trimmed_str)
		return (0);
	while (ft_char_in_charset(*s1, set))
		++s1;
	ft_strlcpy(trimmed_str, s1, trimmed_len + 1);
	return (trimmed_str);
}

char	*get_next_line(int fd)
{
	static t_gnl_vars	x;

	while (x.prv[fd] && x.prv[fd][x.len])
		++x.len;
	x.buf = malloc((size_t)x.len + BUFFER_SIZE + 1);
	x.b = read(fd, x.buf + x.len, BUFFER_SIZE);
	if (x.b < 0)
		return (free(x.buf), free(x.prv[fd]), x.len = 0, x.prv[fd] = NULL);
	(free(NULL), x.buf[x.len + x.b] = 0, x.i = x.len, x.j = -1);
	while (--x.len >= 0)
		x.buf[x.len] = x.prv[fd][x.len];
	while (x.buf[++x.len] && x.buf[x.len] != '\n')
		;
	if (!x.buf[x.len] && x.b == 0 && (free(x.buf), 1))
		return (x.buf = x.prv[fd], x.prv[fd] = NULL, x.len = 0, x.buf);
	if (!x.buf[x.len] && x.b == BUFFER_SIZE && (free(x.prv[fd]), 1))
		return (x.prv[fd] = x.buf, x.len = 0, get_next_line(fd));
	if (!x.buf[x.len] || (x.buf[x.len] == '\n' && !x.buf[x.len + 1]))
		return (free(x.prv[fd]), x.prv[fd] = NULL, x.len = 0, x.buf);
	(free(x.prv[fd]), x.prv[fd] = malloc(sizeof(char) * (size_t)(x.i + ++x.b)));
	if (!x.prv[fd])
		return (free(x.buf), free(x.prv[fd]), x.len = 0, x.prv[fd] = NULL);
	while (x.buf[x.len + 1 + ++x.j])
		x.prv[fd][x.j] = x.buf[x.len + 1 + x.j];
	return (x.prv[fd][x.j] = 0, x.buf[x.len + 1] = 0, x.len = 0, x.buf);
}
