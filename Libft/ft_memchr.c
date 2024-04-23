/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:15:50 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:16:49 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*us;

	us = (unsigned char *)s;
	index = 0;
	while (index < n)
	{
		if (us[index] == (unsigned char)c)
			return (&((unsigned char *)s)[index]);
		index++;
	}
	return (NULL);
}
