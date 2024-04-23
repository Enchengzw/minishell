/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:12:54 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/02 18:15:40 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

static void	ft_update_env(char ***env, int *size, char *variable)
{
	int	index;

	if (ft_is_in_env_index(*env, variable, &index))
	{
		if (ft_strcontains(variable, '='))
		{
			free((*env)[index]);
			(*env)[index] = ft_strdup(variable);
		}
	}
	else
	{
		*size += 1;
		*env = ft_realloc_doublep_char(*env, *size + 1);
		(*env)[(*size) - 1] = ft_strdup(variable);
	}
}

int	ft_export(t_cmd **cmd)
{
	int		i;
	char	**arg;

	arg = (*cmd)->arg;
	i = 1;
	if ((*cmd)->num_arg < 1)
		return (ft_print_sorted_env((*cmd)->env->env[0]));
	while (arg && arg[i])
	{
		if (ft_valid_name(arg[i]))
			return (ft_print_export_error(arg[i]));
		else
			ft_update_env((*cmd)->env->env, &((*cmd)->env->env_size),
				arg[i]);
		i++;
	}
	return (SUCCESS);
}
