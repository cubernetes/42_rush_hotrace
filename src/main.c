/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:53:45 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/10 22:17:57 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_func.h"
#include "../include/ht.h"
#include "../include/utils.h"
#include <stdio.h> /* printf() */ /* TODO: remove printf() */
#include <stdlib.h>
#include <unistd.h>

#define MISSING_VALUE_ERR "Missing value to a key"

void	error(t_kv ht[TABLE_SIZE], const char *msg)
{
	printf("%s\n", msg);
	close(0);
	get_next_line(0);
	ht_destroy(ht);
	exit(EXIT_FAILURE);
}

int	populate_ht(t_kv ht[TABLE_SIZE])
{
	char		*key;
	char		*value;

	while (1)
	{
		key = get_next_line(0);
		if (!key)
		{
			ht_destroy(ht);
			return (0);
		}
		if (key[0] == '\n' && key[1] == '\0')
			break ;
		value = get_next_line(0);
		if (!value)
			(free(key), error(ht, MISSING_VALUE_ERR));
		if (value[0] == '\n' && value[1] == '\0')
			(free(key), free(value), error(ht, MISSING_VALUE_ERR));
		ht_set(ht, key, value);
	}
	free(key);
	return (1);
}

int	main(void)
{
	static t_kv	ht[TABLE_SIZE];
	char		*key;
	char		*value;
	char		*tmp;

	if (!populate_ht(ht))
		return (0);
	while (1)
	{
		key = get_next_line(0);
		if (!key)
			break ;
		value = ht_get(ht, key);
		tmp = ft_strtrim(key, "\n");
		free(key);
		if (value == NULL)
			printf("%s: Not found\n", tmp);
		else
			printf("%s", value);
		free(tmp);
	}
	ht_destroy(ht);
	return (0);
}
