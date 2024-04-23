/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 13:26:29 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/28 13:27:26 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_list_size(t_cmd *cmd)
{
	int	count;

	count = 0;
	while (cmd)
	{
		count +=1;
		cmd = cmd->next;
	}
	return (count);
}