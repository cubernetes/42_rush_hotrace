/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 21:33:37 by tosuman           #+#    #+#             */
/*   Updated: 2024/03/10 17:38:02 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ht.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h> /* printf() */ /* TODO: remove printf() */

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
