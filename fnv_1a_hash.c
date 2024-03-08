/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fnv_1a_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:09:30 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/08 22:53:44 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_func.h"

uint32_t	fnv_1a_32(char *input_str)
{
	unsigned char	*str;
	uint32_t		hash;

	str = (unsigned char *) input_str;
	hash = OFFSET_BASIS_32;
	while (*str)
	{
		hash ^= (unsigned int) *str;
		hash *= FNV_PRIME_32;
		str++;
	}
	return (hash);
}

uint64_t	fnv_1a_64(char *input_str)
{
	unsigned char	*str;
	uint64_t		hash;

	str = (unsigned char *) input_str;
	hash = OFFSET_BASIS_64;
	while (*str)
	{
		hash ^= (unsigned long) *str;
		hash *= FNV_PRIME_64;
		str++;
	}
	return (hash);
}
