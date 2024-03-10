/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:53:45 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/10 23:37:59 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_func.h"
#include "../include/ht.h"
#include "../include/utils.h"
#include "../include/gnl.h"
#include <stdio.h> /* printf() */ /* TODO: remove printf() */
#include <stdlib.h>
#include <unistd.h>

#define MISSING_VALUE_ERR "Missing value to a key"

void	error(t_kv ht[TABLE_SIZE], const char *msg)
{
	char	*line;

	printf("%s\n", msg);
	while (1)
	{
		line = get_next_line_stdin().str;
		if (line == NULL)
			break ;
		free(line);
	}
	ht_destroy(ht);
	exit(EXIT_FAILURE);
}

int	populate_ht(t_kv ht[TABLE_SIZE])
{
	char		*key;
	char		*value;

	while (1)
	{
		key = get_next_line_stdin().str;
		if (!key)
			break ;
		value = get_next_line_stdin().str;
		if (!value)
			(free(key), error(ht, MISSING_VALUE_ERR));
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

	if (!populate_ht(ht))
		return (0);
	while (1)
	{
		key = get_next_line_stdin().str;
		if (!key)
			break ;
		value = ht_get(ht, key);
		if (value == NULL)
			printf("%s: Not found\n", key);
		else
			printf("%s\n", value);
		free(key);
	}
	ht_destroy(ht);
	return (0);
}
