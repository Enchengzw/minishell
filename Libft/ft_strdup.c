/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:03:45 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/23 12:37:05 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dpointer_size(char **args)
{
	int		i;

	i = 0;
	while (args && args[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dupe;
	int		index;
	int		length;

	length = ft_strlen(s);
	index = 0;
	dupe = (char *)malloc(sizeof(char) * (length + 1));
	if (!dupe)
		return (NULL);
	while (index < length)
	{
		dupe[index] = s[index];
		index++;
	}
	dupe[index] = '\0';
	return (dupe);
}

char	**ft_dpointer_dupe(char **original)
{
	char	**new;
	int		i;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (ft_dpointer_size(original) + 1));
	while (original && original[i])
	{
		new[i] = ft_strdup(original[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}