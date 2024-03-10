/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:17:45 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/10 23:20:30 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# define BUFFER_SIZE 64
# define ALLOC_SIZE 1

typedef struct s_pair
{
	char			*str;
	unsigned int	len;
}	t_pair;

t_pair	*ft_realloc(t_pair *datas, unsigned int old_size,
			unsigned int new_size);
void	copy(char *buf, char *datas, unsigned int begin, unsigned int count);
int		ft_strcmp(const char *s1, const char *s2);
t_pair	*ft_free_str(char **str, t_pair *ret);
char	*ft_strndup(const char *s1, unsigned int n);
t_pair	get_next_line_stdin(void);

#endif
