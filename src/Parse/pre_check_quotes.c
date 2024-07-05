/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:33:31 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/26 21:01:20 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//39 simple quotes
//34 Double quotes

static int	ft_check_in_quote(char *s, int *i)
{
	char	q;

	q = 0;
	if (s[*i] == 34)
		q = 34;
	else if (s[*i] == 39)
		q = 39;
	(*i)++;
	while (s[*i] && (s[*i] != q || (s[*i + 1] == q && s[*i] == '\\')
			|| (s[*i] == q && s[*i - 1] == '\\')))
		(*i)++;
	if (!s[*i])
		return (1);
	(*i)++;
	return (0);
}

int	ft_pre_check_quotes(char *input)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			if (ft_check_in_quote(input, &i) == 1)
				return (1);
		}
		else
			i++;
	}
	return (0);
}
