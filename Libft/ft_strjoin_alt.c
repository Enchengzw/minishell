/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_alt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:41:39 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:18:13 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_alt(char *s1, char *s2, int length)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	result = (char *)malloc(sizeof(char) * length);
	if (!result)
		return (NULL);
	while (s1 && s1[i] && i < (length - 1))
	{
		result[i] = s1[i];
		i++;
	}
	while (i < (length - 1) && s2 && s2[j])
	{
		result[i] = s2[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}
