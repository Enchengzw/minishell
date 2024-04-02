/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:22:34 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/02 18:12:20 by ezhou            ###   ########.fr       */
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
		printf("%s\n", env[0][i]);
		i++;
	}
	return (SUCCESS);
}
