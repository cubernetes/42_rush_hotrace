/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 22:44:01 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/10 23:23:56 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/utils.h"
#include <stdlib.h>

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
