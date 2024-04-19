/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:43:52 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/18 10:43:02 by rauferna         ###   ########.fr       */
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

static char	*getarray(const char *s, char c)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && (s[i] != c || (s[i + 1] == c && s[i] == '\\')))
	{
		if (s[i] == '\\' && s[i + 1] && s[i + 1] != 'n')
		{
			res[j] = s[i + 1];
			i += 2;
		}
		/*else if (s[i] == '\\' && s[i + 1] && s[i + 1] != 'n')
			i++;*/
		else
			res[j] = s[i++];
		j++;
	}
	res[i] = '\0';
	return (res);
}

static char	*check_quotes(char *str, const char *s)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			res = getarray(s + 1, 39);
			free(str);
			return (res);
		}
		else if (str[i] == 34)
		{
			res = getarray(s + 1, 34);
			free(str);
			return (res);
		}
		i++;
	}
	return (str);
}

char	**free_mem(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	**ft_split_mod(char const *s, char c)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	len = repsc(s, c);
	res = malloc(sizeof(char *) * ((len + 1)));
	if (!res)
		return (NULL);
	while (*s && i < len)
	{
		while (*s && *s == c)
			s++;
		res[i] = getarray(s, c);
		if (!res[i])
			return (free_mem(res));
		res[i] = check_quotes(res[i], s);
		s += ft_strlen(res[i]);
		i++;
		while (*s && *s != c)
			s++;
	}
	res[i] = 0;
	return (res);
}
