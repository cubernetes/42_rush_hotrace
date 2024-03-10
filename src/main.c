/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:53:45 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/10 18:00:17 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/hash_func.h"
#include "../include/ht.h"
#include "../include/utils.h"
#include <stdio.h> /* printf() */ /* TODO: remove printf() */
#include <stdlib.h>               /* free() */

/* TODO: fix leaks */
int	test_hash_table(int argc, char **argv)
{
	static t_kv	ht[TABLE_SIZE];
	char		*key;
	char		*value;

	(void)argc;
	(void)argv;
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

int	test_hash_funcs(int argc, char **argv)
{
	char	*inp;

	if (argc == 2)
	{
		inp = argv[1];
		printf("FNV:\n");
		printf("32-bit Hash for `%s` = %u\n", inp, fnv_1a_32(inp));
		printf("64-bit Hash for `%s` = %lu\n", inp, fnv_1a_64(inp));
		printf("\nFasthash:\n");
		printf("32-bit Hash for `%s` = %u\n", inp, fasthash_32(inp,
				ft_strlen(inp), 42));
		printf("64-bit Hash for `%s` = %lu\n", inp, fasthash_64(inp,
				ft_strlen(inp), 42));
	}
	else
		printf("Usage: %s <string to be hashed>\n", argv[0]);
	return (0);
}

int	main(int argc, char **argv)
{
	return (test_hash_table(argc, argv));
	/* return (test_hash_funcs(argc, argv)); */
}
