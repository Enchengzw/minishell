/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:43:52 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/01 20:20:14 by rauferna         ###   ########.fr       */
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

static void	getarray_loop(char *str, int *i, int *j, const char *s)
{
	str[*j++] = s[*i + 1];
	(*i) += 2;
}

static char	*getarray(const char *s, char c, int n)
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
	if (s[i] == c && n == 1)
		res[j++] = s[i++];
	while (s[i] && (s[i] != c || (s[i + 1] == c && s[i] == '\\')))
	{
		if (s[i] == '\\' && s[i + 1] && s[i + 1] != 'n' && s[i + 1] == c)
			getarray_loop(res, &i, &j, s);
		else
			res[j++] = s[i++];
	}
	if (s[i] == c && n == 1)
		res[j] = s[i++];
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
			res = ft_strjoin(ft_substr(str, 0, i), getarray(s + i, str[i], 1));
			free(str);
			return (res);
		}
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_mod_pipe(char const *s, char c)
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
		res[i] = getarray(s, c, 0);
		if (!res[i])
			return (ft_free_char(res), NULL);
		res[i] = check_quotes(res[i], s);
		s += ft_strlen(res[i]);
		i++;
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
