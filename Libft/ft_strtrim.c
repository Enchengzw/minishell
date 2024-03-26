/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:20:53 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:19:01 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_included(char c, const char *set)
{
	int	index;

	index = 0;
	while (set[index])
	{
		if (set[index] == c)
			return (1);
		index++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		index;
	int		start;
	int		end;
	char	*new;

	index = 0;
	if (!s || !set)
		return (NULL);
	while (s[index] && ft_is_included(s[index], set))
	{
		index++;
	}
	start = index;
	index = ft_strlen(s) - 1;
	if (index < 0)
		index = 0;
	while (s[index] && ft_is_included(s[index], set))
	{
		index--;
	}
	end = index;
	new = ft_substr(&(s[start]), 0, end - start + 1);
	return (new);
}
