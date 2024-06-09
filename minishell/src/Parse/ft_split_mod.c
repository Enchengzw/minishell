/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:43:52 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/16 17:20:12 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_strlen_nospaces(char const *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
			i++;
		else
		{
			while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
				i++;
			j++;
		}
	}
	return (j);
}

static char	*getarray_spaces(const char *s, char c)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	if (!*s || *s == c)
		return (ft_strdup(" "));
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && (s[i] != c || (s[i + 1] == c && s[i] == '\\')))
	{
		if (s[i] == '\\' && (s[i + 1] == c || s[i + 1] == ' '))
		{
			res[j] = s[i + 1];
			i += 2;
		}
		else
			res[j] = s[i++];
		j++;
	}
	res[i] = '\0';
	return (res);
}

static void	check_backslash(char *res, const char *s, int *i, int *j)
{
	if (s[*i] == '\\' && (s[*i + 1] == ' '
			|| s[*i + 1] == '\t' || s[*i + 1] == '\n'))
	{
		res[*j] = s[*i + 1];
		*i += 2;
	}
	else
		res[*j] = s[(*i)++];
	(*j)++;
}

static char	*check_quotes_spaces(const char *s)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (s[i] && (s[i] != ' ' && s[i] != '\t' && s[i] != '\n'))
	{
		if ((s[i] == 39 || s[i] == 34))
		{
			res = ft_strjoin_allocs1(res,
					getarray_spaces(s + i + 1, s[i]));
			i = ft_strlen(res) + 2;
		}
		else
			check_backslash(res, s, &i, &j);
	}
	res[i] = '\0';
	return (res);
}

char	**ft_split_mod(char const *s)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	len = ft_strlen_nospaces(s);
	res = ft_calloc((len + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (*s && i < len)
	{
		while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
			s++;
		res[i] = check_quotes_spaces(s);
		if (!res[i])
			return (ft_free_char(res), NULL);
		s += ft_strlen(res[i++]);
		while (*s && (*s != ' ' && *s != '\t' && *s != '\n'))
			s++;
	}
	res[i] = 0;
	return (res);
}
