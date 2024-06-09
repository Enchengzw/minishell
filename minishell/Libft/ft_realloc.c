/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:08:43 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/07 12:32:46 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_doublep_char(char **ptr, size_t size)
{
	char	**new;
	size_t	i;

	i = 0;
	new = ft_calloc(size, sizeof(char *));
	while (ptr && ptr[i] && i < size)
	{
		new[i] = ft_strdup(ptr[i]);
		i++;
	}
	ft_free_char(ptr);
	return (new);
}
