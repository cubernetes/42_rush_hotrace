/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:45:39 by tosuman           #+#    #+#             */
/*   Updated: 2024/03/10 19:16:50 by astavrop         ###   ########.fr       */
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

size_t	ft_strlen(const char *s)
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
