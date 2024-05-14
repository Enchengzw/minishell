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

void	ft_get_exit_code(char *str, int *j, int *i)
{
	int		len;
	int		exit_code;
	char	buffer[4];

	len = 0;
	if (g_exit_code == 0)
		str[(*j)++] = '0';
	exit_code = g_exit_code;
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
	*i = *(i + 2);
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
			ft_get_exit_code(res, &j, &i);
		else if (str[i] == '$' && cmd->quote != 2 && str[i + 1] != '?')
		{
			if (ft_getenv(str + i + 1, *(cmd->env->env)) == NULL)
				return (res);
			res = ft_strjoin(res, ft_getenv(str + i + 1, *(cmd->env->env)));
			return (res);
		}
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (res);
}
