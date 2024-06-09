/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:37:24 by ezhou             #+#    #+#             */
/*   Updated: 2023/10/19 15:17:32 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_pointer(size_t lnbr, char *base)
{
	size_t	length;
	int		result;

	result = 0;
	length = ft_strlen(base);
	if (lnbr < length)
	{
		result += ft_putchar(base[lnbr]);
	}
	else
	{
		result += ft_print_pointer(lnbr / length, base);
		result += ft_putchar(base[lnbr % length]);
	}
	return (result);
}

static int	ft_print_selector(va_list arg, char format)
{
	if (format == 'c')
		return (ft_putchar(va_arg(arg, int)));
	else if (format == 's')
		return (ft_putstr(va_arg(arg, char *)));
	else if (format == 'p')
		return (ft_putstr("0x") + ft_print_pointer(va_arg(arg, size_t),
				"0123456789abcdef"));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr_base(va_arg(arg, int), "0123456789"));
	else if (format == 'u')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789"));
	else if (format == 'x')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (format == 'X')
		return (ft_putnbr_base(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	else if (format == '%')
		return (ft_putchar(format));
	return (INT_MIN);
}

int	ft_printf(char const *str, ...)
{
	va_list	arg;
	int		count;
	int		index;

	count = 0;
	index = -1;
	va_start(arg, str);
	if (!str)
		return (0);
	while (str[++index])
	{
		if (str[index] == '%')
			count += ft_print_selector(arg, str[++index]);
		else
			if (str[index])
				count += ft_putchar(str[index]);
		if (count < 0)
			return (-1);
	}
	va_end(arg);
	return (count);
}
