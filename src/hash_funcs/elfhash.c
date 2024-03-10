/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elfhash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 17:14:54 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/10 18:33:53 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_func.h"

uint32_t	elf_hash_32(char *input_str)
{
	uint32_t		hash;
	uint32_t		g;
	unsigned char	*str;

	hash = 0;
	g = 0;
	str = (unsigned char *)input_str;
	while (*str)
	{
		hash = (hash << 4) + *str++;
		g = hash & 0xf0000000;
		if (g)
			hash ^= g >> 24;
		hash &= ~g;
	}
	return (hash);
}

uint32_t	elf_gnu_hash_32(char *input_str)
{
	uint32_t		hash;
	unsigned char	c;
	unsigned char	*str;

	str = (unsigned char *) input_str;
	hash = 5381;
	c = *str;
	while (*str)
		hash = (hash << 5) + hash + *str++;
	return (hash & 0xffffffff);
}
