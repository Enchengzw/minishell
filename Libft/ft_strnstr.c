/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:19:05 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:18:53 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	index;
	size_t	length;

	length = ft_strlen(little);
	index = 0;
	if (!little[0])
		return ((char *)big);
	while (big[index] && index < len)
	{
		if (big[index] == little[0])
		{
			if (ft_strncmp(&(big[index]), little, length) == 0 && index
				+ length <= len)
				return ((char *)&(big[index]));
		}
		index++;
	}
	return (NULL);
}
