/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:14:34 by ezhou             #+#    #+#             */
/*   Updated: 2023/12/11 13:53:57 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*pointer;

	pointer = (char *)malloc(sizeof(char) * size);
	if (!pointer)
		return (NULL);
	ft_memset(pointer, '\0', size);
	return (pointer);
}

int	ft_number_length(long n)
{
	int	counter;

	counter = 0;
	if (n == 0)
		counter += 1;
	if (n < 0)
		counter += 1;
	while (n != 0)
	{
		n = n / 10;
		counter += 1;
	}
	return (counter);
}

char	*ft_itoa(long ln)
{
	char	*list;
	int		length;

	length = ft_number_length(ln);
	list = ft_strnew(length + 1);
	if (!list)
		return (NULL);
	if (ln < 0)
		list[0] = '-';
	if (ln == 0)
		list[length - 1] = '0';
	list[length] = '\0';
	while (ln != 0)
	{
		if (ln % 10 < 0)
			list[length - 1] = ((ln % 10) * -1) + '0';
		else
			list[length - 1] = (ln % 10) + '0';
		length--;
		ln /= 10;
	}
	return (list);
}
/*
int	main(void)
{
	char	*str;

	str = ft_itoa(9223372036854775807);
	printf("%s\n", str);
	return (0);
}
*/