/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rauferna <rauferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:46:53 by rauferna          #+#    #+#             */
/*   Updated: 2024/04/29 16:39:15 by rauferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_redirections_init(t_cmd *cmd, t_data *data)
{
	if (cmd->fds)
	{
		if (cmd->fds->infile)
			close(cmd->fds->infile);
		if (cmd->fds->outfile)
			close(cmd->fds->outfile);
	}
	cmd->fds = ft_calloc(1, sizeof(t_fds));
	if (!cmd->fds)
		return (ERROR);
	cmd->fds->std_in = data->std_in;
	cmd->fds->std_out =data->std_out;
	return (SUCCESS);
}

static void	continue_redirections(char **args, int *i, t_cmd *cmd)
{
	if (ft_strncmp(args[*i], ">>", 2) != 0
		&& ft_strncmp(args[*i], "<<", 2) != 0)
	{
		if (ft_strncmp(args[*i], "<", 1) == 0)
		{
			if (ft_strlen(args[*i]) == 1)
				cmd->fds->infile = openfile(args[*i + 1], 1);
			else
				cmd->fds->infile = openfile(args[*i] + 1, 1);
		}
		else if (ft_strncmp(args[*i], ">", 1) == 0)
		{
			if (ft_strlen(args[*i]) == 1)
				cmd->fds->outfile = openfile(args[*i + 1], 2);
			else
				cmd->fds->outfile = openfile(args[*i] + 1, 2);
		}
	}
	if (cmd->fds->infile && cmd->fds->infile != -1)
		cmd->infile_flag = 1;
	if (cmd->fds->outfile && cmd->fds->outfile != -1)
		cmd->outfile_flag = 1;
}

int	check_redirections(char **args, int i, t_cmd *cmd, t_data *data)
{
	if (ft_redirections_init(cmd, data) == 1)
		return (-1);
	if (!args[i + 1] && (ft_strlen(args[i]) == 2 && (args[i][1] == '<'
			|| args[i][1] == '>') || ft_strlen(args[i]) == 1))
	{
		error_syntax(args[i]);
		return (-1);
	}
	else if (ft_strncmp(args[i], ">>", 2) == 0)
	{
		if (ft_strlen(args[i]) == 2)
			cmd->fds->outfile = openfile(args[i + 1], 3);
		else
			cmd->fds->outfile = openfile(args[i] + 2, 3);
	}
	else if (ft_strncmp(args[i], "<<", 2) == 0)
	{
		if (ft_here_doc(args, i, cmd) == 1)
			return (1);
	}
	continue_redirections(args, &i, cmd);
	if (cmd->fds->outfile == -1 || cmd->fds->infile == -1)
		return (-1);
	return (1);
}
