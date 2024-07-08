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

static char	*ft_copy_special_no_dollar(char *str, int *i, char **res)
{
	int		j;
	char	*tmp;
	char	*tmp2;

	j = 1;
	tmp = ft_strdup(str + *i);
	if (!tmp)
	{
		free(*res);
		*res = NULL;
		ft_putstr_fd("Error: malloc failed\n", 2);
		return (NULL);
	}
	tmp2 = ft_substr(tmp, 0, j);
	while (tmp[j] && ft_special_character(tmp[j]) == 0)
		j++;
	(*res) = ft_strjoin_allocs1(*res, tmp2, 0);
	free(tmp);
	tmp = NULL;
	free(tmp2);
	tmp2 = NULL;
	return (*res);
}

static void	ft_join_and_free(char **res, char *str, int *i, t_cmd *cmd)
{
	char	*getenv;

	getenv = ft_getenv(str + *i + 1, *(cmd->env->env));
	(*res) = ft_strjoin_allocs1(*res, getenv, 0);
	free(str);
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
			else if (str[*i] == '$' && (str[*i + 1]
					&& ft_special_character(str[*i + 1]) == 0
					&& str[*i - 1] != 39))
			{
				ft_join_and_free(res, str, i, cmd);
			}
			else
				(*res) = ft_copy_special_no_dollar(str, i, res);
			(*i)++;
		}
		while (str[*i] && ft_special_character(str[*i]) == 0)
			(*i)++;
	}
}

static void	vergulilla(char **str, int *i, int *k, t_cmd *cmd)
{
	char	*tmp;
	char	*home;

	home = NULL;
	if (str[0][*i] == '~' && cmd->type[*k] == 'v')
	{
		tmp = *str;
		*str = ft_strdup(*str + 1);
		home = ft_getenv("HOME", *(cmd->env->env));
		*str = ft_strjoin_allocs1(home, *str, 0);
		home = NULL;
		free(tmp);
		tmp = NULL;
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
		vergulilla(&str, &i, k, cmd);
		if (str[i] == '$' && (str[i + 1] && cmd->type[*k] != 's'))
			return (ft_copy_char_env(&res, str, &i, cmd), res);
		else
			res[j++] = str[i++];
	}
	res[j] = '\0';
	return (free(tmp), tmp = NULL, res);
}
