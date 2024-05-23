/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:33:31 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/23 13:07:12 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//39 simple quotes
//34 Double quotes
static int	ft_check_spaces(char *str, int i, char quote)
{
	while (str[i] && str[i] != quote)
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count_quotes(char *input)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (input[i])
	{
		if (input[i] == 34)
			quotes++;
		i++;
	}
	if (!(quotes % 2 == 0))
		return (1);
	i = 0;
	quotes = 0;
	while (input[i])
	{
		if (input[i] == 39)
			quotes++;
		i++;
	}
	if (!(quotes % 2 == 0))
		return (1);
	else
		return (0);
}

/* static int	ft_check_next_quote(char *str, int i, char quote)//creo que no se usa
{
	while (str[i])
	{
		if (str[i] == quote)
			return (0);
		i++;
	}
	return (1);
//if (input[*i] == quote && input[*i + 1] == quote)
//	{
//		if (input[*i])
//			res[(*j)++] = input[(*i)++];
//		if (input[*i])
//			res[(*j)++] = input[*i];
//	}
} */

static int	ft_check_in_quote(char *input, char *res, int *i, int *j)
{
	int		k;
	char 	quote;

	k = 0;
	if (input[*i] == 34)
		quote = 34;
	else if (input[*i] == 39)
		quote = 39;
	if (ft_check_spaces(input, *i + 1, quote) == 1)
		res[(*j)++] = input[*i];
	(*i)++;
	k = *i;
	while (input[*i] && input[*i] != quote)
		res[(*j)++] = input[(*i)++];
	if (!input[*i])
		return (1);
	if (ft_check_spaces(input, k, quote) == 1 && input[*i] == quote)
		res[(*j)++] = input[*i];
	(*i)++;
	if (quote == 34)
		return (3);
	else
		return (2);
}

char	*ft_pre_check_quotes(char *input, int *quote)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	if (ft_count_quotes(input) == 1)
		return (NULL);
	res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			*quote = ft_check_in_quote(input, res, &i, &j);
			if (*quote == 1)
				return (NULL);
		}
		else
			res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}
