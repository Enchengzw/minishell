/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dpointer_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:08:03 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/30 12:16:47 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dpointer_size(char **pointer)
{
	int	i;

	i = 0;
	while (pointer[i])
	{
		i++;
	}
	return (i);
}
