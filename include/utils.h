/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:47:15 by tosuman           #+#    #+#             */
/*   Updated: 2024/03/10 19:17:38 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H 1

# include <stddef.h>
# include <sys/types.h>

# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct s_gnl_vars
{
	char	*prv[OPEN_MAX];
	char	*buf;
	ssize_t	b;
	int		i;
	int		j;
	int		len;
}			t_gnl_vars;

int			ft_strcmp(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strdup(char *s);
int			ft_char_in_charset(char c, char const *charset);
char		*ft_strtrim(char const *s1, char const *set);
char		*get_next_line(int fd);
char		*ft_strtrim(char const *s1, char const *set);

#endif /* utils.h. */
