/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:43:52 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/16 20:01:20 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	repsc(char const *s, char c)
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
/*
static void	getarray_loop(char *res, int *i, int *j, const char *s, char c)
{
	if (s[*i] == '\\' && s[*i + 1] == c)
		res[*j++] = s[*i++];
	//(*i)++;
	if (s[*i] == c)
		res[*j++] = s[*i++];
}*/

static char	*getarray(const char *s, char c, int n)
{
	int		i;
	int		j;
	char	*res;

	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));//len exacta
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	if (s[i] == c && n == 1)
		res[j++] = s[i++];
	while (s[i] && (s[i] != c || (s[i + 1] == c && s[i] == '\\') 
		|| (s[i] == c && s[i - 1] == '\\') ) )
	{
		res[j++] = s[i++];
	}
	if (s[i] == c && n == 1)
		res[j++] = s[i];
	res[j] = '\0';
	return (res);
}

static char	*check_quotes(char *str, const char *s, int a)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i])
	{
		if ((str[i] == 39 || str[i] == 34))
		{
			if (a == 0)
				res = getarray(s + i + 1, str[i], 0);
			else
			{
				res = ft_strjoin(ft_substr(str, 0, i),
						getarray(s + i, str[i], 1));
			}
			free(str);
			return (res);
		}
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split_mod_pipe(char const *s, char c, int a)
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
		res[i] = check_quotes(res[i], s, a);
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
