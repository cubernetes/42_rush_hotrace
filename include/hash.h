/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:49:42 by tosuman           #+#    #+#             */
/*   Updated: 2024/03/08 23:50:07 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASH_H
# define HASH_H 1

# define TABLE_SIZE 30

typedef struct s_kv
{
	char		*k;
	char		*v;
	struct s_kv	*n;
}				t_kv;

#endif /* hash.h. */
