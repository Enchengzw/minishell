/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:19:32 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:18:56 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	index;

	index = ft_strlen(s);
	while (s[index] != (unsigned char)c && index > 0)
	{
		index--;
	}
	if (s[index] == (unsigned char)c)
		return (&(((char *)s)[index]));
	else
		return (NULL);
}
