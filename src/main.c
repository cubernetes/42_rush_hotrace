/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:53:45 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/08 22:55:27 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_func.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		char	*inp = av[1];

		printf("32-bit Hash for `%s` = %u\n", inp, fnv_1a_32(inp));
		printf("64-bit Hash for `%s` = %lu\n", inp, fnv_1a_64(inp));
	}
	else
		printf("Usage: %s <string to be hashed>\n", av[0]);
	return (0);
}
