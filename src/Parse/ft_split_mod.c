/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:43:52 by rauferna          #+#    #+#             */
/*   Updated: 2024/07/09 19:18:41 by rauferna         ###   ########.fr       */
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

int	getarray_spaces(const char *s, char **res, int *j, int *k)
{
	char	c;

	if (s == NULL || res == NULL || *res == NULL)
		return (1);
	c = s[*k];
	(*k)++;
	while (s[*k] && (s[*k] != c || (s[*k + 1] == c && s[*k] == '\\')))
	{
		if (s[*k] == '\\' && (s[*k + 1] == c || s[*k + 1] == ' '))
		{
			(*res)[*j] = s[*k + 1];
			*k += 2;
		}
		else
			(*res)[*j] = s[(*k)++];
		(*j)++;
	}
	(*k)++;
	return (0);
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

static char	*check_quotes_spaces(const char *s, int *k, int *i, t_cmd *cmd)
{
	int		j;
	char	*res;

	j = 0;
	res = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_check_type(s, cmd, i, k);
	while (s[*k] && (s[*k] != ' ' && s[*k] != '\t' && s[*k] != '\n'))
	{
		if ((s[*k] == 39 || s[*k] == 34))
		{
			if (getarray_spaces(s, &res, &j, k) == 1)
				return (free(res), NULL);
		}
		else
			check_backslash(res, s, k, &j);
	}
	res[j] = '\0';
	return (res);
}

char	**ft_split_mod(char const *s, t_cmd *cmd)
{
	int		i;
	int		k;
	int		len;
	char	**res;

	i = 0;
	len = ft_strlen_nospaces(s);
	res = ft_calloc((len + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (*s && i < len)
	{
		k = 0;
		while (*s && (*s == ' ' || *s == '\t' || *s == '\n'))
			s++;
		res[i] = check_quotes_spaces(s, &k, &i, cmd);
		if (!res[i])
			return (ft_free_char(res), NULL);
		s += k;
		cmd->num_i = i++;
		while (*s && (*s != ' ' && *s != '\t' && *s != '\n'))
			s++;
	}
	res[i] = 0;
	return (res);
}
