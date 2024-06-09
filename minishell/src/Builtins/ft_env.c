/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:22:34 by ezhou             #+#    #+#             */
/*   Updated: 2024/06/04 13:02:50 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	ft_env(t_cmd **cmd)
{
	int		i;
	char	***env;

	env = (*cmd)->env->env;
	i = 0;
	while (i < (*cmd)->env->env_size)
	{
		if (ft_strcontains(env[0][i], '='))
			printf("%s\n", env[0][i]);
		i++;
	}
	return (SUCCESS);
}
