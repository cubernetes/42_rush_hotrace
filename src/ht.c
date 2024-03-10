/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:33:37 by tosuman           #+#    #+#             */
/*   Updated: 2024/03/10 18:43:21 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ht.h"
#include "../include/hash_func.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h> /* printf() */ /* TODO: remove printf() */

uint64_t	hash(char *key)
{
	return (fnv_1a_64(key));
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

char	*ht_get(t_kv ht[TABLE_SIZE], char *key)
{
	t_kv	*kv;

	kv = &ht[hash(key) % TABLE_SIZE];
	while (kv && kv->k && ft_strcmp(kv->k, key))
		kv = kv->n;
	if (kv && kv->k)
		return (kv->v);
	return (NULL);
}

void	ht_print(t_kv ht[TABLE_SIZE])
{
	int		i;
	t_kv	*kv;
	int		j;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		printf("%d: ", i);
		kv = &ht[i];
		j = 0;
		while (1)
		{
			if (!kv || !kv->k)
				break ;
			if (j++ > 0)
				printf(" -> ");
			printf("\033[31m%s\033[m:\033[32m%s\033[m", ft_strtrim(kv->k, "\n"),
				ft_strtrim(kv->v, "\n"));
			kv = kv->n;
		}
		printf("\n");
	}
}

void	ht_destroy(t_kv ht[TABLE_SIZE])
{
	int		i;
	t_kv	*prev;
	t_kv	*kv;
	int		j;

	i = -1;
	while (++i < TABLE_SIZE)
	{
		kv = &ht[i];
		if (kv->k == NULL)
			continue ;
		j = 0;
		while (kv)
		{
			free(kv->k);
			free(kv->v);
			prev = kv;
			kv = kv->n;
			if (j > 0)
				free(prev);
			++j;
		}
	}
}
