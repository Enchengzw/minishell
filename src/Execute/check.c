/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:17:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/19 11:24:09 by rauferna         ###   ########.fr       */
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
	t_cmd	*temp;

	if (!data || !data->cmd)
		return (SUCCESS);
	temp = data->cmd;
	while (temp)
	{
		if (temp->cmd_flag == 0)
			return (ERROR);
		/*if (ft_check_fds(temp))
			return (ERROR);*/
		temp = temp->next;
	}
	return (INT_MIN);
}

/*
		 int k = 0;
        while (temp->arg[k])
            ft_printf("%s\n", temp->arg[k++]);
		ft_printf("--------\n");
*/