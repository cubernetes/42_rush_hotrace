/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:33:37 by tosuman           #+#    #+#             */
/*   Updated: 2024/03/08 23:40:45 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdint.h>

#define TABLE_SIZE 30

#ifndef OPEN_MAX
# define OPEN_MAX 4096
#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct s_all
{
	char		*prv[OPEN_MAX];
	char		*buf;
	ssize_t		bread;
	int			i;
	int			j;
	int			len;
}				t_gnl_vars;

typedef struct s_kv
{
	char		*k;
	char		*v;
	struct s_kv	*n;
}				t_kv;

char			*ft_strtrim(char const *s1, char const *set);

char	*get_next_line(int fd)
{
	static t_gnl_vars	x;

	while (x.prv[fd] && x.prv[fd][x.len])
		++x.len;
	x.buf = malloc(x.len + BUFFER_SIZE + 1);
	x.bread = read(fd, x.buf + x.len, BUFFER_SIZE);
	if (x.bread < 0)
		return (free(x.buf), free(x.prv[fd]), x.len = 0, x.prv[fd] = NULL);
	(free(NULL), x.buf[x.len + x.bread] = 0, x.i = x.len, x.j = -1);
	while (--x.len >= 0)
		x.buf[x.len] = x.prv[fd][x.len];
	while (x.buf[++x.len] && x.buf[x.len] != '\n')
		;
	if (!x.buf[x.len] && x.bread == 0 && (free(x.buf), 1))
		return (x.buf = x.prv[fd], x.prv[fd] = NULL, x.len = 0, x.buf);
	if (!x.buf[x.len] && x.bread == BUFFER_SIZE && (free(x.prv[fd]), 1))
		return (x.prv[fd] = x.buf, x.len = 0, get_next_line(fd));
	if (!x.buf[x.len] || (x.buf[x.len] == '\n' && !x.buf[x.len + 1]))
		return (free(x.prv[fd]), x.prv[fd] = NULL, x.len = 0, x.buf);
	(free(x.prv[fd]), x.prv[fd] = malloc(sizeof(char) * (x.i + x.bread + 1)));
	if (!x.prv[fd])
		return (free(x.buf), free(x.prv[fd]), x.len = 0, x.prv[fd] = NULL);
	while (x.buf[x.len + 1 + ++x.j])
		x.prv[fd][x.j] = x.buf[x.len + 1 + x.j];
	return (x.prv[fd][x.j] = 0, x.buf[x.len + 1] = 0, x.len = 0, x.buf);
}

int	hash(char *key)
{
	int	sum;

	sum = 0;
	while (*key)
		sum += (int) *key++;
	return (sum);
}

void	ht_set(t_kv ht[TABLE_SIZE], char *key, char *value)
{
	int		idx;
	t_kv	*new_kv;

	idx = hash(key) % TABLE_SIZE;
	if (!ht[idx].k)
	{
		ht[idx].k = key;
		ht[idx].v = value;
		ht[idx].n = NULL;
	}
	else
	{
		new_kv = malloc(sizeof(*new_kv));
		new_kv->k = key;
		new_kv->v = value;
		new_kv->n = ht[idx].n;
		ht[idx].n = new_kv;
	}
}

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

char	*ht_get(t_kv ht[TABLE_SIZE], char *key)
{
	t_kv	*kv;

	kv = &ht[hash(key) % TABLE_SIZE];
	while (kv && kv->k && ft_strcmp(kv->k, key))
		kv = kv->n;
	if (kv && kv->k)
		return (kv->v);
	return ("key not found\n");
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

void	print_linked_list(t_kv kv_)
{
	t_kv	*kv;
	int		i;

	kv = &kv_;
	i = 0;
	while (1)
	{
		if (!kv || !kv->k)
			break ;
		if (i++ > 0)
			printf(" -> ");
		printf("\033[31m%s\033[m:\033[32m%s\033[m", ft_strtrim(kv->k, "\n"),
			ft_strtrim(kv->v, "\n"));
		kv = kv->n;
	}
	printf("\n");
}

void	ht_print(t_kv ht[TABLE_SIZE])
{
	int	i;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		printf("%d: ", i);
		print_linked_list(ht[i]);
	}
}

int	main(void)
{
	static t_kv	ht[TABLE_SIZE];
	char		*key;
	char		*value;

	while (1)
	{
		key = get_next_line(0);
		value = get_next_line(0);
		if (!key || !value)
		{
			free(key);
			free(value);
			break ;
		}
		ht_set(ht, key, value);
	}
	ht_print(ht);
	printf("\n%s", ht_get(ht, "3lI73sJOlT6BZkGEOEr8\n"));
	return (0);
}
