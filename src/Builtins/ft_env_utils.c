/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:19:42 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/22 18:55:02 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static size_t ft_strlen_no_spaces(const char *s)//que vea si le afecta
{
	size_t i;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '/')
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
		if (!ft_strncmp(variable, env[i], ft_strlen_no_spaces(variable)))
		{
			if (ft_strcontains(env[i], '=') && env[i][ft_strlen_no_spaces(variable)] == '=')
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

int		ft_valid_name(char	*string)
{
	int	i;

	i = 0;
	if (string[i] == '=')
		return (ERROR);
	while (string[i] && string[i] != '=')
	{
		if (i == 0)
		{
			if (!ft_isalpha(string[i]))
				return (ERROR);
		}
		else
		{
			if (!ft_isalnum(string[i]))
			{
				if (string[i] == '_')
					;
				else
					return (ERROR);
			}
		}
		i++;
	}
	return (SUCCESS);
}

int		ft_is_in_env_index(char **env, char *variable, int *index, int *flag)
{
	char	*key;
	char	**temp;
	int		i;

	i = 0;
	*flag = 0;
	temp = ft_split(variable, '=');
	if (!temp)
		return (ft_putstr_fd("Malloc Error\n", 2), ERROR);
	key = temp[0];
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], ft_strlen(key)))
		{
			*flag = 1;
			*index = i;
			break ;
		}
		i++;
	}
	ft_free_char(temp);
	return (SUCCESS);
}

int		ft_print_export_error(char *variable)
{
	printf("export: `%s': not a valid identifier\n", variable);
	return (ERROR);
}
