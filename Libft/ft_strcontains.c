/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcontains.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:00:25 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:18:02 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcontains(char *s, int c)
{
	int	index;

	index = 0;
	if (!s || *s == 0)
		return (0);
	while (s[index])
	{
		if (s[index] == c)
			return (1);
		index++;
	}
	return (0);
}
