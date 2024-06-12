/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:04:00 by rauferna          #+#    #+#             */
/*   Updated: 2024/06/12 19:12:38 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_special_character(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == ','
		|| c == '{' || c == '}' || c == '[' || c == ']' || c == '"'
		|| c == '\'' || c == '\\' || c == '#' || c == '&' || c == '*'
		|| c == '?' || c == '/' || c == ':' || c == '@' || c == '='
		|| c == '$' || c == '%' || c == '-')
		return (1);
	else
		return (0);
}

char	*ft_strjoin_allocs1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(sizeof(char), (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	free(s2);
	return (str);
}

static char	*ft_copy_special_no_dollar(char *str, int *i, char **res)
{
	int		j;
	char	*tmp;

	j = 1;
	tmp = ft_strdup(str + *i);
	while (tmp[j] && ft_special_character(tmp[j]) == 0)
		j++;
	free(tmp);
	return (ft_strjoin(*res, ft_substr(str, *i, j)));
}

static void	ft_copy_char_env(char **res, char *str, int *i, t_cmd *cmd)
{
	while (str[*i])
	{
		if (str[*i] && (ft_special_character(str[*i]) == 1))
		{
			if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
			{
				(*res) = ft_strjoin_allocs1(*res, ft_itoa(*(cmd->exit_code)));
				(*i)++;
			}
			else if (str[*i] == '$' && str[*i + 1]
				&& ft_special_character(str[*i + 1]) == 0)
			{
				(*res) = ft_strjoin_allocs1(*res, ft_getenv(str + *i + 1,
							*(cmd->env->env)));
				if ((*res) == NULL)
					(*res) = ft_strdup("");
			}
			else
				(*res) = ft_copy_special_no_dollar(str, i, res);
			(*i)++;
		}
		while (str[*i] && ft_special_character(str[*i]) == 0)
			(*i)++;
	}
}

char	*ft_copy_char(char *str, int *k, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] && cmd->type[*k] != 's'))
			return (ft_copy_char_env(&res, str, &i, cmd), res);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
