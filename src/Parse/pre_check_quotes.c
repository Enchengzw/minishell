/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:33:31 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/26 13:10:20 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

static int	ft_check_next_quote(char *str, int i, char quote)
{
	while (str[i])
	{
		if (str[i] == quote)
			return (0);
		i++;
	}
	return (1);
}

static void	ft_check_in_quote_simple(char *input, char *res, int *i, int *j)
{
	int	k;

	k = 0;
	if (ft_check_spaces(input, *i + 1, 39) == 1
		|| ft_check_next_quote(input, *i + 1, 39) == 1)
		res[(*j)++] = input[*i];
	(*i)++;
	k = *i;
	while (input[*i] != 39)
		res[(*j)++] = input[(*i)++];
	if (ft_check_spaces(input, k, 39) == 1 && input[*i] == 39)
		res[(*j)++] = input[*i];
	else
		return ;
	(*i)++;
}

static void	ft_check_in_quote_double(char *input, char *res, int *i, int *j)
{
	int	k;

	k = 0;
	if (ft_check_spaces(input, *i + 1, 34) == 1)
		res[(*j)++] = input[*i];
	(*i)++;
	k = *i;
	while (input[*i] != 34)
		res[(*j)++] = input[(*i)++];
	if (ft_check_spaces(input, k, 34) == 1 && input[*i] == 34)
		res[(*j)++] = input[*i];
	else
		return ;
	(*i)++;
}

char	*pre_check_quotes(char *input)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(input), sizeof(char));
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] == 34)
			ft_check_in_quote_double(input, res, &i, &j);
		else if (input[i] == 39)
			ft_check_in_quote_simple(input, res, &i, &j);
		else
			res[j++] = input[i++];//arreglar para cuando hay muchas comillas seguidas
	}
	return (res);
}
