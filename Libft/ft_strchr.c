/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:03:38 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:18:00 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	index;

	index = 0;
	while (s[index] && s[index] != (unsigned char)c)
	{
		index++;
	}
	if (s[index] == (unsigned char)c)
		return (&(((char *)s)[index]));
	else
		return (NULL);
}
