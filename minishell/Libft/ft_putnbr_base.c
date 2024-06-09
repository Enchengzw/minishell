/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 10:38:56 by ezhou             #+#    #+#             */
/*   Updated: 2023/11/27 16:32:39 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_base(long lnbr, char *base)
{
	long	length;
	int		result;

	result = 0;
	length = ft_strlen(base);
	if (lnbr < 0)
	{
		result += ft_putchar('-');
		lnbr *= -1;
	}
	if (lnbr < length)
	{
		result += ft_putchar(base[lnbr]);
	}
	else
	{
		result += ft_putnbr_base(lnbr / length, base);
		result += ft_putchar(base[lnbr % length]);
	}
	return (result);
}
