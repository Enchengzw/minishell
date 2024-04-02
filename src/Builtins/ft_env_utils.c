/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:19:42 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/02 18:14:27 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_valid_name(char	*string)
{
	int	i;

	i = 0;
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

int	ft_is_in_env_index(char **env, char *variable, int *index)
{
	char	*key;
	char	**temp;
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	temp = ft_split(variable, '=');
	key = temp[0];
	while (env[i])
	{
		if (!ft_strncmp(key, env[i], ft_strlen(key)))
		{
			flag = 1;
			*index = i;
			break ;
		}
		i++;
	}
	ft_free_char(temp);
	return (flag);
}

int	ft_print_export_error(char *variable)
{
	printf("export: `%s': not a valid identifier\n", variable);
	return (ERROR);
}
