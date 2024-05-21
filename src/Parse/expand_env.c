/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:04:00 by rauferna          #+#    #+#             */
/*   Updated: 2024/05/14 17:41:18 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*ft_strjoin_allocs1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
	{
		s1 = ft_calloc(sizeof(char), 1);
		s1[0] = '\0';
	}
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
	return (str);
}

void	ft_get_exit_code(char *str, int *j, int *i, t_cmd *cmd)
{
	int		len;
	int		exit_code;
	char	buffer[4];

	len = 0;
	if ((cmd->exit_code) == 0)
	{
		str[(*j)++] = '0';
		*i += 2;
		return ;
	}
	exit_code = cmd->exit_code;
	while (exit_code > 0)
	{
		buffer[len++] = (exit_code % 10) + '0';
		exit_code /= 10;
	}
	while (len > 0)
	{
		str[*j] = buffer[--len];
		(*j)++;
	}
	*i += 2;
}

char	*ft_copy_char(char *str, t_cmd *cmd)
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
		if (str[i + 1] && str[i] == '$' && str[i + 1] == '?' && cmd->quote != 2)
			ft_get_exit_code(res, &j, &i, cmd);
		else if (str[i] == '$' && cmd->quote != 2 && str[i + 1] != '?')
		{
			res = ft_strjoin_allocs1(res, ft_getenv(str + i + 1, *(cmd->env->env)));
			return (res);
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
