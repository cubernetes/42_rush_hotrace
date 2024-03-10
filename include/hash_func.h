/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astavrop <astavrop@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 22:11:19 by astavrop          #+#    #+#             */
/*   Updated: 2024/03/08 22:54:10 by astavrop         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_FUNC_H
# define HASH_FUNC_H

# include <stdint.h>
# include <stddef.h>

// FNV

# define OFFSET_BASIS_32  2166136261
# define OFFSET_BASIS_64  14695981039346656037UL

# define FNV_PRIME_32  16777619
# define FNV_PRIME_64  1099511628211UL

uint32_t		fnv_1a_32(char *input_str);
uint64_t		fnv_1a_64(char *input_str);

// FASTHASH

# define M 0x880355f21e6d1965ULL

uint64_t		fasthash_64(char *input_str, size_t len, uint64_t seed);
uint32_t		fasthash_32(char *input_str, size_t len, uint32_t seed);

#endif
