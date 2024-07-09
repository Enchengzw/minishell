/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:35:00 by rauferna          #+#    #+#             */
/*   Updated: 2024/07/09 12:39:43 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_special_character(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == ','
		|| c == '{' || c == '}' || c == '[' || c == ']' || c == '"'
		|| c == '\'' || c == '\\' || c == '#' || c == '&' || c == '*'
		|| c == '?' || c == '/' || c == ':' || c == '@' || c == '='
		|| c == '$' || c == '%' || c == '-' || c == '~' || c == '|')
		return (1);
	else
		return (0);
}

char	*ft_strjoin_allocs1(char *s1, char *s2, int num)
{
	char	*str;

	if (!s1)
	{
		s1 = ft_calloc(1, sizeof(char));
		if (!s1)
			return (NULL);
	}
	if (!s2)
	{
		s2 = ft_calloc(1, sizeof(char));
		if (!s2)
			return (NULL);
	}
	str = ft_strjoin(s1, s2);
	if (!str)
		return (NULL);
	if (num == 1 || num == 0)
		free(s1);
	s1 = NULL;
	if (num == 0 || num == 2)
		free(s2);
	s2 = NULL;
	return (str);
}

int	ft_copy_tilde(char **str, int *i, int *k, t_cmd *cmd)
{
	char	*tmp;
	char	*home;

	home = NULL;
	if (str[0][*i] == '~' && cmd->type[*k] == 'v')
	{
		tmp = *str;
		*str = ft_strdup(*str + 1);
		if (!*str)
			return (ft_putstr_fd("Error: Malloc error\n", 2), 1);
		home = ft_getenv("HOME", *(cmd->env->env));
		if (!home)
			return (ft_putstr_fd("Error: HOME not set\n", 2), 1);
		*str = ft_strjoin_allocs1(home, *str, 0);
		if (!*str)
			return (ft_putstr_fd("Error: Malloc error\n", 2), 1);
		home = NULL;
		free(tmp);
		tmp = NULL;
	}
	return (0);
}
