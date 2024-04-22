/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:17:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/04/22 11:47:12 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_check_fds(t_fds *io)
{
	if (!io || !io->infile || !io->outfile)
		return (ERROR);
	return (SUCCESS);
}

void	create_fds(t_cmd *cmd)
{
	cmd->fds = ft_calloc(1, sizeof(t_fds));
	if (!cmd->fds)
	{
		ft_putstr_fd("Malloc Error\n", STDERR);
		return ;
	}
	if (cmd->outfile_flag == 0)
		cmd->fds->outfile = -1;
	if (cmd->infile_flag == 0)
		cmd->fds->infile = -1;
}

int	ft_check_data(t_data *data)
{
	t_cmd	*temp;

	if (!data || !data->cmd)
		return (SUCCESS);
	temp = data->cmd;
	while (temp)
	{
		//si es -1 el fd salir
		if (temp->file_flag == -1 || temp->cmd_flag <= 0)
			return (ERROR);
		if (temp->infile_flag == 0 || temp->outfile_flag == 0)
			create_fds(data->cmd);
		if (ft_check_fds(temp->fds))
			return (ERROR);
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