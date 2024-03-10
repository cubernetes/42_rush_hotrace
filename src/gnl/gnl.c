/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 23:18:15 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/10 23:25:07 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include <stdlib.h>
#include <unistd.h>

static t_pair	ft_strjoin(t_pair p1, t_pair p2)
{
	t_pair			new;
	unsigned int	i;
	unsigned int	j;

	new.len = p1.len + p2.len;
	new.str = malloc(sizeof(char) * (new.len + 1));
	if (!new.str)
		return ((t_pair){NULL, 0});
	i = 0;
	while (i < p1.len)
	{
		new.str[i] = p1.str[i];
		i++;
	}
	j = 0;
	while (j < p2.len)
		new.str[i++] = p2.str[j++];
	new.str[new.len] = '\0';
	return (new);
}

static int	search_eol(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		if (str[i++] == '\n')
			return (i);
	return (-1);
}

static t_pair	split(t_pair *saved, int eol)
{
	char	*tmp;
	t_pair	new;

	new = (t_pair){ft_strndup((*saved).str, eol - 1), eol - 1};
	tmp = ft_strndup((*saved).str + eol, (*saved).len - eol);
	free((*saved).str);
	(*saved).str = tmp;
	(*saved).len -= eol;
	if (!(*saved).len)
	{
		free((*saved).str);
		(*saved) = (t_pair){NULL, 0};
	}
	if (!new.len)
	{
		free(new.str);
		new = (t_pair){NULL, 0};
	}
	return (new);
}

static int	get_line(t_pair *saved, int *tmp)
{
	char	*old;
	char	buffer[BUFFER_SIZE + 1];
	int		eol;
	int		result;

	eol = -1;
	result = BUFFER_SIZE;
	while (eol == -1 && result == BUFFER_SIZE)
	{
		result = read(0, buffer, BUFFER_SIZE);
		if (result == -1)
			return (-2);
		if (!result)
			return (-1);
		buffer[result] = '\0';
		eol = search_eol(buffer);
		if (eol != -1)
			*tmp = (*saved).len + eol;
		old = (*saved).str;
		*saved = ft_strjoin(*saved, (t_pair){buffer, result});
		if (!(*saved).str)
			return (-2);
		free(old);
	}
	return (eol);
}

t_pair	get_next_line_stdin(void)
{
	static t_pair	saved = (t_pair){NULL, 0};
	t_pair			new;
	int				eol;
	int				tmp;

	if (saved.len)
	{
		eol = search_eol(saved.str);
		if (eol > -1)
			return (split(&saved, eol));
	}
	eol = get_line(&saved, &tmp);
	if (eol == -2)
		return ((t_pair){NULL, 0});
	if (eol != -1)
		return (split(&saved, tmp));
	new = saved;
	free(saved.str);
	saved = (t_pair){NULL, 0};
	return (new);
}
