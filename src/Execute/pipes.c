/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:18:16 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/26 18:15:17 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_create_pipes(t_data *data)
{
	t_cmd *temp;
	
	temp = data->cmd;
	while(temp)
	{
		if (pipe(temp->fds->pipe) == -1)
			return (ERROR);
		temp = temp->next;
	}
	return (SUCCESS)
}

void	ft_prep_io(t_data *data)
{
	t_cmd 	*temp;
	t_cmd	*next;
	
	temp = data->cmd;
	while(temp)
	{
		next = temp->next;
		if (next)
		{
			if (!temp->fds->infile)
				temp->fds->infile = temp->fds->pipe[0];
			if (!temp->fds->outfile)
				temp->fds->outfile = temp->fds->pipe[1];
			
		}
		temp = temp->next;
	}
	return (SUCCESS)
}
