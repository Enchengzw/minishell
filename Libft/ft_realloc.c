/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: encheng <encheng@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:08:43 by ezhou             #+#    #+#             */
/*   Updated: 2024/07/02 14:05:27 by encheng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_doublep_char(char **ptr, size_t size)
{
	char	**new;
	size_t	i;

	i = 0;
	new = ft_calloc(size, sizeof(char *));
	if (!new)
		return (NULL);
	while (ptr && ptr[i] && i < size)
	{
		new[i] = ft_strdup(ptr[i]);
		i++;
	}
	ft_free_char(ptr);
	return (new);
}
