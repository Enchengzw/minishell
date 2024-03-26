/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchrindex.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:19:32 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/20 17:34:43 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrchrindex(const char *s, int c)
{
	size_t	index;

	index = ft_strlen(s);
	while (s[index] != (unsigned char)c && index > 0)
	{
		index--;
	}
	if (s[index] == (unsigned char)c)
		return (index);
	else
		return (0);
}
