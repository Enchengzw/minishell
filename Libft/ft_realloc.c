/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:08:43 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/20 18:47:37 by rauferna         ###   ########.fr       */
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
