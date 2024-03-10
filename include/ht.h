/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tosuman <timo42@proton.me>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:49:42 by tosuman           #+#    #+#             */
/*   Updated: 2024/03/10 17:36:07 by tosuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HT_H
# define HT_H 1

# define TABLE_SIZE 30

typedef struct s_kv
{
	char		*k;
	char		*v;
	struct s_kv	*n;
}				t_kv;

void			ht_set(t_kv ht[TABLE_SIZE], char *key, char *value);
char			*ht_get(t_kv ht[TABLE_SIZE], char *key);
void			ht_print(t_kv ht[TABLE_SIZE]);

#endif /* ht.h. */
