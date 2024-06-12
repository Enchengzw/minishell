/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:43:52 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/04 18:56:43 by rauferna         ###   ########.fr       */
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

static char	*getarray(const char *s, char c, int *n)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (s[i] == c)
		res[j++] = s[i++];
	while (s[i] && (s[i] != c || (s[i + 1] == c && s[i] == '\\')
			|| (s[i] == c && s[i - 1] == '\\')))
		res[j++] = s[i++];
	if (s[i] == c)
		res[j++] = s[i];
	res[j] = '\0';
	*n = j + *n;
	return (res);
}

static char	*check_quotes(const char *s, int *k)
{
	int		j;
	char	*res;

	j = 0;
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[*k])
	{
		if ((s[*k] == 39 || s[*k] == 34))
		{
			res = ft_strjoin_allocs1(res,
					getarray(s + *k, s[*k], k));
			j = ft_strlen(res);
		}
		else
		{
			if (s[*k] == '|')
				break ;
			res[j++] = s[(*k)++];
		}
	}
	if (s[*k] != '|')
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
