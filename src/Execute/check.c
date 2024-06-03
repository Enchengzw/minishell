/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:17:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/27 12:45:36 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_fds(t_cmd *cmd, t_data *data)
{
	if (cmd->file_flag == 0)
	{
		cmd->fds = ft_calloc(1, sizeof(t_fds));
		if (!cmd->fds)
		{
			ft_putstr_fd("Malloc Error\n", STDERR);
			return ;
		}
	}
	if (cmd->outfile_flag == 0)
		cmd->fds->outfile = -1;
	if (cmd->infile_flag == 0)
		cmd->fds->infile = -1;
	cmd->fds->std_in = data->std_in;
	cmd->fds->std_out = data->std_out;
}

int	ft_check_data(t_data *data)
{
	t_cmd	*temp;

	if (!data || !data->cmd)
		return (SUCCESS);
	temp = data->cmd;
	while (temp)
	{
		if (temp->two_points == 1 && temp->cmd_flag == 0)
			return (0);
		if (temp->file_flag == -1)
			return (1);
		if (temp->cmd_flag == -1)
			return (127);
		if (temp->infile_flag == 0 || temp->outfile_flag == 0)
			create_fds(temp, data);
		temp = temp->next;
	}
	return (INT_MIN);
}
