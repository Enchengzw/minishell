/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 17:04:00 by rauferna          #+#    #+#             */
/*   Updated: 2024/07/09 19:07:01 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*ft_copy_special_no_dollar(char *str, int *i, char **res)
{
	int		j;
	char	*tmp;

	j = 1;
	tmp = ft_strdup(str + *i);
	while (tmp[j] && ft_special_character(tmp[j]) == 0)
		j++;
	(*res) = ft_strjoin_allocs1(*res, ft_substr(tmp, 0, j), 0);
	if ((*res) == NULL)
		(*res) = ft_strdup("");
	free(tmp);
	return (*res);
}

static void	ft_copy_char_env(char **res, char *str, int *i, t_cmd *cmd)
{
	while (str[*i])
	{
		if (str[*i] && (ft_special_character(str[*i]) == 1))
		{
			if (str[*i] == '$' && str[*i + 1] && str[*i + 1] == '?')
			{
				(*res) = ft_strjoin_allocs1(*res,
						ft_itoa(*(cmd->exit_code)), 0);
				(*i)++;
			}
			else if (str[*i] == '$' && str[*i + 1]
				&& ft_special_character(str[*i + 1]) == 0)
			{
				(*res) = ft_strjoin_allocs1(*res, ft_getenv(str + *i + 1,
							*(cmd->env->env)), 0);
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

char	*ft_copy_env(char *str, int *k, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*res;
	char	*tmp;

	i = 0;
	j = 0;
	res = (char *)ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		tmp = str;
		if (str[i] == '~' && cmd->type[*k] == 'h')
			ft_copy_tilde(&str, &i, k, cmd);
		if (str[i] == '$' && (str[i + 1] && cmd->type[*k] != 's'))
			return (ft_copy_char_env(&res, str, &i, cmd), free(str), res);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (free(tmp), res);
}
