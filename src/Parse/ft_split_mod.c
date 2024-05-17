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

static char	*getarray(const char *s, char c)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] && (s[i] != c || (s[i + 1] == c && s[i] == '\\')))
	{
		if (s[i] == '\\' && s[i + 1] && s[i + 1] != 'n' && s[i + 1] == c)
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

static char	*check_quotes(char *str, const char *s)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 39 || str[i] == 34))
		{
			res = getarray(s + i + 1, str[i]);
			if (res[0] == '\0')
				return (free(str), NULL);
			free(str);
			return (res);
		}
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_mod(char const *s, char c)
{
	int		i;
	int		len;
	char	**res;

	i = 0;
	len = repsc(s, c);
	res = ft_calloc((len + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (*s && i < len)
	{
		while (*s && *s == c)
			s++;
		res[i] = getarray(s, c);
		if (!res[i])
			return (ft_free_char(res), NULL);
		res[i] = check_quotes(res[i], s);
		s += ft_strlen(res[i++]);
		while (*s && *s != c)
			s++;
	}
	res[i] = 0;
	return (res);
}

/*else if (s[i] == '\\' && s[i + 1] && s[i + 1] != 'n')
	i++;
		while (s[i] && (s[i] != c || (s[i + 1] == c && s[i] == '\\')))
	{
		if (s[i] == '\\' && s[i + 1] && s[i + 1] != 'n')
		{
			res[j] = s[i + 1];
			i += 2;
		}
		else
			res[j] = s[i++];
		j++;
	}
	*/
