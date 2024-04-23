/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:19:58 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/02 17:08:33 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free(char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}

static int	ft_count_word(char const *s, char c)
{
	int	index;
	int	count;

	if (*s != c && *s != '\0')
		count = 1;
	else
		count = 0;
	index = 0;
	while (s[index])
	{
		if (s[index] == c && s[index + 1] != c && s[index + 1])
			count += 1;
		index++;
	}
	return (count);
}

static int	ft_strlen_char(char const *s, char c)
{
	int	index;

	index = 0;
	while (s[index] && s[index] != c)
		index++;
	return (index);
}

static char	*ft_strnewc(char const *s, char c, char *array_cell, int *index)
{
	int	length;

	length = ft_strlen_char(s, c);
	array_cell = (char *)malloc(sizeof(char) * (length + 1));
	if (!array_cell)
		return (NULL);
	ft_strlcpy(array_cell, s, length + 1);
	*index += length - 1;
	return (array_cell);
}

char	**ft_split(char const *s, char c)
{
	int		index;
	char	**array;
	int		array_index;

	index = -1;
	array_index = 0;
	array = (char **)ft_calloc(sizeof(char *), (ft_count_word(s, c) + 1));
	if (!array)
		return (NULL);
	while (s[++index])
	{
		if (s[index] != c)
		{
			array[array_index] = ft_strnewc(&(s[index]), c, array[array_index],
					&index);
			if (!array[array_index])
			{
				ft_free(array);
				return (NULL);
			}
			array_index++;
		}
	}
	array[array_index] = NULL;
	return (array);
}
