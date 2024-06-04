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
	res[j++] = '\0';
	*n = j + *n;
	return (res);
}

static char	*check_quotes(const char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if ((s[i] == 39 || s[i] == 34))
			res = ft_strjoin_allocs1(res,
					getarray(s + i, s[i], &i));
		else
		{
			if (s[i] == '|')
				break ;
			res[j++] = s[i++];
		}
	}
	res[i] = '\0';
	return (res);
}

char	**ft_split_mod_pipe(char const *s)
{
	int		i;
	int		len;
	char	c;
	char	**res;

	i = 0;
	c = '|';
	len = repsc(s, c);
	res = ft_calloc((len + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (*s && i < len)
	{
		while (*s && *s == c)
			s++;
		res[i] = check_quotes(s);
		s += ft_strlen(res[i]);
		if (!res[i])
			return (ft_free_char(res), NULL);
		i++;
		while (*s && *s != c)
			s++;
	}
	res[i] = 0;
	return (res);
}
