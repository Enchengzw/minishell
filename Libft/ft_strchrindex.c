/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrindex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:27:49 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/20 17:28:04 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strchrindex(char *s, int c)
{
	int	index;

	index = 0;
	if (!s || *s == 0)
		return (0);
	while (s[index])
	{
		if (s[index] == c)
			return (index);
		index++;
	}
	return (0);
}
