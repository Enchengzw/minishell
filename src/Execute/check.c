/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:17:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/03 11:43:03 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_fds(t_fds *io)
{
	if (!io || !io->infile || !io->outfile)
		return (ERROR);
	return (SUCCESS);
}
 
int	ft_check_data(t_data *data)
{
	t_cmd *temp;
	
	if (!data || !data->cmd)
		return (SUCCESS);
	temp = data->cmd;
	while(temp)
	{
		if (ft_check_fds(temp->fds))
			return (ERROR);
		temp = temp->next;
	}
	return (INT_MIN);
}
