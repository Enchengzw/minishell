/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:19:42 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/27 12:41:45 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static size_t	ft_strlen_no_special(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_special_character(s[i]) == 0)
		i++;
	return (i);
}

char	*ft_getenv(char *variable, char **env)
{
	int		i;
	char	*value;
	char	*to_copy;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(variable, env[i], ft_strlen_no_special(variable)))
		{
			if (ft_strcontains(env[i], '=')
				&& env[i][ft_strlen_no_special(variable)] == '=')
			{
				to_copy = ft_strchr(env[i], '=') + 1;
				value = ft_strdup(to_copy);
				if (!value)
					return (ft_putstr_fd("Malloc Error\n", 2), NULL);
				return (value);
			}
		}
		i++;
	}
	return (NULL);
}

int	ft_valid_name(char *string)
{
	int	i;

	i = 0;
	if (string[i] == '=' || (!ft_isalpha(string[i]) && string[i] != '_'))
		return (ERROR);
	while (string[++i] && string[i] != '=')
	{
		if (!ft_isalnum(string[i]))
		{
			if (string[i] == '_')
				;
			else if (string[i] == '+' && string[i + 1] && string[i + 1] == '=')
				;
			else
				return (ERROR);
		}
	}
	return (SUCCESS);
}

int	ft_is_in_env_index(char **env, char *variable, int *index, int *flag)
{
	char	*key;
	char	**temp;
	int		i;

	i = 0;
	*flag = 0;
	temp = ft_split(variable, '=');
	if (!temp)
		return (ft_putstr_fd("Malloc Error\n", 2), ERROR);
	key = ft_strtrim(temp[0], "+");
	if (!key)
		return (ft_putstr_fd("Malloc Error\n", 2), ft_free_char(temp), ERROR);
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], ft_strlen(key))
			&& (!(env[i][ft_strlen(key)]) || env[i][ft_strlen(key)] == '='))
		{
			*flag = 1;
			*index = i;
			break ;
		}
		i++;
	}
	return (free(key), ft_free_char(temp), SUCCESS);
}

int	ft_print_export_error(char *variable)
{
	printf("export: `%s': not a valid identifier\n", variable);
	return (ERROR);
}
