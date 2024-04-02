/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:30:18 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/02 18:18:12 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static int	ft_update_env(char ***env, int size, int index)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = ft_calloc(size, sizeof(char *));
	while (env && *env && (*env)[i])
	{
		if (i != index)
		{
			new[j] = ft_strdup((*env)[i]);
			j++;
		}
		i++;
	}
	ft_free_char(*(env));
	*env = new;
	return (SUCCESS);
}

int	ft_unset(t_cmd **cmd)
{
	int		i;
	char	**arg;
	int		index;

	arg = (*cmd)->arg;
	i = 0;
	if ((*cmd)->num_arg < 1)
		return (SUCCESS);
	while (arg[++i])
	{
		if (ft_valid_name(arg[i]))
			return (ft_print_export_error(arg[i]));
		else
		{
			if (ft_is_in_env_index((*cmd)->env->env[0], arg[i], &index))
			{
				ft_update_env((*cmd)->env->env, (*cmd)->env->env_size,
					index);
				(*cmd)->env->env_size -= 1;
			}
			else
				return (SUCCESS);
		}
	}
	return (SUCCESS);
}
