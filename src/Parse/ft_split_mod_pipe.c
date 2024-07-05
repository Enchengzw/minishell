/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:43:52 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/25 12:17:54 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	repsc(char const *s, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			j++;
		}
	}
	return (j);
}

static int	getarray(const char *s, char **res, int *k, int *j)
{
	char	c;

	if (s == NULL || res == NULL || *res == NULL)
		return (1);
	c = s[*k];
	(*res)[(*j)++] = s[(*k)++];
	while (s[*k] && (s[*k] != c || (s[*k + 1] == c && s[*k] == '\\')))
	{
		if (s[*k] == '\\' && (s[*k + 1] == c || s[*k + 1] == ' '))
		{
			(*res)[*j] = s[*k + 1];
			(*k) += 2;
		}
		else
			(*res)[*j] = s[(*k)++];
		(*j)++;
	}
	(*res)[(*j)++] = s[(*k)++];
	return (0);
}

static char	*check_quotes(const char *s, int *k)
{
	int		j;
	char	*res;

	j = 0;
	res = ft_calloc(ft_strlen(s) + 1 + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[*k])
	{
		if ((s[*k] == 39 || s[*k] == 34))
		{
			getarray(s, &res, k, &j);
		}
		else
		{
			if (s[*k] == '|')
				break ;
			res[j++] = s[(*k)++];
		}
	}
	res[*k] = '\0';
	return (res);
}

char	**ft_split_mod_pipe(char const *s)
{
	int		i;
	int		k;
	int		len;
	char	**res;

	i = 0;
	len = repsc(s, '|');
	res = ft_calloc((len + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (*s && i < len)
	{
		k = 0;
		while (*s && *s == '|')
			s++;
		res[i] = check_quotes(s, &k);
		if (!res[i])
			return (ft_free_char(res), NULL);
		s += k;
		i++;
		while (*s && *s != '|')
			s++;
	}
	res[i] = 0;
	return (res);
}
