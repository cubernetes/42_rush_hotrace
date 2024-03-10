/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fasthash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 14:01:50 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/10 15:30:09 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_func.h"

uint64_t	mix_64(uint64_t hash)
{
	hash ^= (hash) >> 23;
	hash *= 0x2127599bf4325c37ULL;
	hash ^= (hash) >> 47;
	return (hash);
}

static void	fasthash64_switch(size_t len, unsigned char *pos2, uint64_t *hash,
		uint64_t *v)
{
	if ((len & 7) == 7)
		*v ^= (uint64_t)pos2[6] << 48;
	else if ((len & 7) == 6)
		*v ^= (uint64_t)pos2[5] << 40;
	else if ((len & 7) == 5)
		*v ^= (uint64_t)pos2[4] << 32;
	else if ((len & 7) == 4)
		*v ^= (uint64_t)pos2[3] << 24;
	else if ((len & 7) == 3)
		*v ^= (uint64_t)pos2[2] << 16;
	else if ((len & 7) == 2)
		*v ^= (uint64_t)pos2[1] << 8;
	else if ((len & 7) == 1)
	{
		*v ^= (uint64_t)pos2[0];
		*hash ^= mix_64(*v);
		*hash *= M;
	}
}

uint64_t	fasthash_64(char *input_str, size_t len, uint64_t seed)
{
	uint64_t		*pos;
	uint64_t		*end;
	unsigned char	*pos2;
	uint64_t		hash;
	uint64_t		v;

	pos = (uint64_t *) input_str;
	end = pos + (len / 8);
	hash = seed ^ (len * M);
	while (pos != end)
	{
		v = *pos++;
		hash ^= mix_64(v);
		hash *= M;
	}
	pos2 = (unsigned char *) pos;
	v = 0;
	fasthash64_switch(len, pos2, &hash, &v);
	return (mix_64(hash));
}

uint32_t	fasthash_32(char *input_str, size_t len, uint32_t seed)
{
	uint64_t	hash;

	hash = fasthash_64(input_str, len, seed);
	return (hash - (hash >> 32));
}
