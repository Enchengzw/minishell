/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:17:20 by ezhou             #+#    #+#             */
/*   Updated: 2024/05/01 16:35:19 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
int	ft_check_fds(t_fds *io)
{
	if (!io || !io->infile || !io->outfile)
		return (ERROR);
	return (SUCCESS);
}
*/

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
	//ft_printf("Dsa da\ninfile: %d\noutfile: %d\n", cmd->fds->infile, cmd->fds->outfile);
}

int	ft_check_data(t_data *data)
{
	t_cmd	*temp;

	if (!data || !data->cmd)
		return (SUCCESS);
	temp = data->cmd;
	while (temp)
	{
		if (temp->file_flag == -1 || temp->cmd_flag <= 0)
			return (ERROR);
		//ft_printf("No errors\ninfile: %d\noutfile: %d\n", temp->infile_flag, temp->outfile_flag);
		if (temp->infile_flag == 0 || temp->outfile_flag == 0)
			create_fds(temp, data);
		//ft_printf("Create fd OK\n");
		//ft_printf("A A\ninfile: %d\noutfile: %d\n", temp->fds->infile, temp->fds->outfile);
		//ft_printf("-------------------------------------------------------------------\n");
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