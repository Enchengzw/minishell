/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_check_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:33:31 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/25 17:39:09 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//39 simple quotes
//34 Double quotes

static int	ft_check_special(char *str, int i, char quote)
{
	while (str[i] && str[i] != quote)
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
			|| str[i] == '$' || str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}

static int	ft_check_in_quote(char *input, char *res, int *i, int *j)
{
	int		k;
	char	quote;

	k = 0;
	quote = 0;
	if (input[*i] == 34)
		quote = 34;
	else if (input[*i] == 39)
		quote = 39;
	if (ft_check_special(input, *i + 1, quote) == 1)
		res[(*j)++] = input[*i];
	(*i)++;
	k = (*i);
	while (input[*i] && (input[*i] != quote))
		res[(*j)++] = input[(*i)++];
	if (!input[*i])
		return (1);
	if (ft_check_special(input, k, quote) == 1 && input[*i] == quote)
		res[(*j)++] = input[*i];
	(*i)++;
	return (0);
}

char	*ft_pre_check_quotes(char *input, int *quote)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(input) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
		{
			*quote = ft_check_in_quote(input, res, &i, &j);
			if (*quote == 1)
				return (free(res), NULL);
		}
		else
			res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}
